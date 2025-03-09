// ==UserScript==
// @name         北航研究生抢课脚本
// @namespace    http://tampermonkey.net/
// @version      0.1
// @description  北航研究生抢课助手
// @author       Your name
// @match        https://yjsxk.buaa.edu.cn/*
// @grant        none
// @require      https://code.jquery.com/jquery-3.6.0.min.js
// @run-at       document-start
// ==/UserScript==

(function() {
    'use strict';

    // 创建操作框样式
    const style = `
        .control-panel {
            position: fixed;
            top: 20px;
            right: 20px;
            background: white;
            padding: 15px;
            border-radius: 8px;
            box-shadow: 0 0 10px rgba(0,0,0,0.1);
            z-index: 10000;
            cursor: move;
            user-select: none;
        }
        .control-panel * {
            cursor: auto;
        }
        .control-panel input {
            margin: 5px 0;
            padding: 5px;
            width: 200px;
        }
        .control-panel button {
            margin: 10px 0;
            padding: 5px 15px;
            background: #4CAF50;
            color: white;
            border: none;
            border-radius: 4px;
            cursor: pointer;
        }
        .control-panel button:disabled {
            background: #cccccc;
        }
        .result-area {
            margin-top: 10px;
            padding: 10px;
            border: 1px solid #ddd;
            max-height: 150px;
            overflow-y: auto;
        }
    `;

    // 创建样式元素
    const styleElement = document.createElement('style');
    styleElement.textContent = style;
    document.head.appendChild(styleElement);

    // 添加保存配置的函数
    function saveConfig(kcdm, kclx, interval, autoStart = false) {
        const config = {
            kcdm,
            kclx,
            interval,
            autoStart,
            timestamp: Date.now()
        };
        console.log('保存配置:', config);
        localStorage.setItem('buaaCourseSniperConfig', JSON.stringify(config));
    }

    // 获取配置的函数
    function getConfig() {
        const configStr = localStorage.getItem('buaaCourseSniperConfig');
        return configStr ? JSON.parse(configStr) : null;
    }

    // 添加拖拽功能
    function makeDraggable(panel) {
        let isDragging = false;
        let currentX;
        let currentY;
        let initialX;
        let initialY;

        panel.addEventListener('mousedown', function(e) {
            // 如果点击的是输入框或按钮，不启动拖拽
            if (e.target.tagName === 'INPUT' || e.target.tagName === 'BUTTON') {
                return;
            }
            
            isDragging = true;
            
            // 获取面板当前位置
            const style = window.getComputedStyle(panel);
            const matrix = new WebKitCSSMatrix(style.transform);
            
            initialX = e.clientX - (matrix.m41 || 0);
            initialY = e.clientY - (matrix.m42 || 0);
            
            panel.style.transition = 'none'; // 拖动时禁用过渡效果
        });

        document.addEventListener('mousemove', function(e) {
            if (!isDragging) return;

            e.preventDefault(); // 防止选中文字

            currentX = e.clientX - initialX;
            currentY = e.clientY - initialY;

            // 确保面板不会被拖出视口
            const panelRect = panel.getBoundingClientRect();
            const viewportWidth = window.innerWidth;
            const viewportHeight = window.innerHeight;

            // 限制水平方向
            if (currentX < 0) {
                currentX = 0;
            } else if (currentX + panelRect.width > viewportWidth) {
                currentX = viewportWidth - panelRect.width;
            }

            // 限制垂直方向
            if (currentY < 0) {
                currentY = 0;
            } else if (currentY + panelRect.height > viewportHeight) {
                currentY = viewportHeight - panelRect.height;
            }

            panel.style.transform = `translate(${currentX}px, ${currentY}px)`;
        });

        document.addEventListener('mouseup', function() {
            if (!isDragging) return;
            
            isDragging = false;
            panel.style.transition = 'transform 0.2s'; // 恢复过渡效果
            
            // 保存面板位置到 localStorage
            const position = {
                x: currentX,
                y: currentY
            };
            localStorage.setItem('panelPosition', JSON.stringify(position));
        });
    }

    // 修改初始化面板逻辑
    function initializePanel() {
        console.log('初始化面板...');
        const config = getConfig();
        console.log('config:', config);
        if (config) {
            console.log('找到配置:', config);
            console.log('自动启动:', config.autoStart);
            // 填充表单
            const kcdmInput = document.getElementById('kcdm');
            const kclxInput = document.getElementById('kclx');
            const intervalInput = document.getElementById('interval');
            
            if (kcdmInput && kclxInput && intervalInput) {
                kcdmInput.value = config.kcdm;
                kclxInput.value = config.kclx;
                intervalInput.value = config.interval;

                // 如果标记为自动启动，直接重新开始抢课
                if (config.autoStart) {
                    console.log('准备自动启动抢课...');
                    // 使用setTimeout确保DOM完全加载
                    setTimeout(() => {
                        console.log('执行自动启动...');
                        startSniper(config.kcdm, config.kclx, config.interval);
                    }, 1000);
                }
            }
        }
    }

    // 修改创建面板的代码，确保在DOM ready后执行
    function createAndInitPanel() {
        // 检查面板是否已存在
        if (document.querySelector('.control-panel')) {
            return;
        }

        // 创建面板
        const panel = document.createElement('div');
        panel.className = 'control-panel';
        panel.innerHTML = `
            <h3>抢课助手</h3>
            <div>
                <label>课程代码：</label><br>
                <input type="text" id="kcdm" placeholder="请输入课程代码"><br>
                <label>类型：</label><br>
                <input type="text" id="kclx" placeholder="请输入类型"><br>
                <label>间隔时间(ms)：</label><br>
                <input type="number" id="interval" value="500" min="100"><br>
                <button id="startBtn">开始抢课</button>
                <button id="stopBtn" disabled>停止抢课</button>
            </div>
            <div class="result-area" id="resultArea">
                等待开始...
            </div>
        `;
        document.body.appendChild(panel);

        // 应用拖拽功能
        makeDraggable(panel);

        // 恢复上次保存的位置
        const savedPosition = localStorage.getItem('panelPosition');
        if (savedPosition) {
            const position = JSON.parse(savedPosition);
            panel.style.transform = `translate(${position.x}px, ${position.y}px)`;
        }

        // 绑定按钮事件
        document.getElementById('startBtn').addEventListener('click', () => {
            const kcdm = document.getElementById('kcdm').value;
            const kclx = document.getElementById('kclx').value;
            const interval = parseInt(document.getElementById('interval').value);

            if (!kcdm || !kclx) {
                alert('请填写完整信息！');
                return;
            }

            startSniper(kcdm, kclx, interval);
        });

        document.getElementById('stopBtn').addEventListener('click', stopSniper);

        // 初始化面板配置
        initializePanel();
    }

    // 确保在DOM加载完成后创建面板
    if (document.readyState === 'loading') {
        document.addEventListener('DOMContentLoaded', createAndInitPanel);
    } else {
        createAndInitPanel();
    }

    // 声明全局变量
    let intervalId = null;
    let refreshTimeout = null;

    // 修改发送请求函数
    function sendRequest(kcdm, kclx) {
        try {
            const csrfToken = document.querySelector('#csrfToken');
            if (!csrfToken) {
                console.error('未找到csrfToken');
                return;
            }

            const data = {
                bjdm: kcdm,
                lx: kclx,
                csrfToken: csrfToken.value
            };
            console.log('发送请求:', data);
            
            const urlEncodedData = new URLSearchParams(data).toString();
            const url = 'https://yjsxk.buaa.edu.cn/yjsxkapp/sys/xsxkappbuaa/xsxkCourse/choiceCourse.do?_=' + String(Date.now());

            fetch(url, {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/x-www-form-urlencoded; charset=UTF-8'
                },
                body: urlEncodedData,
                credentials: 'include' // 添加这行确保发送cookies
            })
            .then(response => response.json())
            .then(data => {
                const resultArea = document.getElementById('resultArea');
                const time = new Date().toLocaleTimeString();
                resultArea.innerHTML = `${time}: ${JSON.stringify(data)}<br>` + resultArea.innerHTML;
            })
            .catch(error => {
                console.error('请求失败:', error);
                const resultArea = document.getElementById('resultArea');
                const time = new Date().toLocaleTimeString();
                resultArea.innerHTML = `${time}: 错误: ${error}<br>` + resultArea.innerHTML;
            });
        } catch (error) {
            console.error('请求发送失败:', error);
        }
    }

    // 修改开始抢课函数
    function startSniper(kcdm, kclx, interval) {
        try {
            console.log('开始抢课:', {kcdm, kclx, interval});
            
            // 确保csrfToken存在
            const csrfToken = document.querySelector('#csrfToken');
            if (!csrfToken) {
                console.error('未找到csrfToken，等待1秒后重试');
                setTimeout(() => startSniper(kcdm, kclx, interval), 1000);
                return;
            }
            
            // 保存配置并标记为自动启动
            saveConfig(kcdm, kclx, interval, true);

            // 禁用开始按钮，启用停止按钮
            const startBtn = document.getElementById('startBtn');
            const stopBtn = document.getElementById('stopBtn');
            if (startBtn && stopBtn) {
                startBtn.disabled = true;
                stopBtn.disabled = false;
            }

            // 清除可能存在的旧定时器
            if (intervalId) {
                clearInterval(intervalId);
                intervalId = null;
            }
            if (refreshTimeout) {
                clearTimeout(refreshTimeout);
                refreshTimeout = null;
            }

            // 开始定时发送请求
            intervalId = setInterval(() => sendRequest(kcdm, kclx), interval);

            // 设置刷新
            refreshTimeout = setTimeout(() => {
                console.log('准备刷新页面...');
                // 保存配置确保刷新后可以自动启动
                saveConfig(kcdm, kclx, interval, true);
                window.location.reload();
            }, 60000);

        } catch (error) {
            console.error('启动失败:', error);
            // 如果失败，1秒后重试
            setTimeout(() => startSniper(kcdm, kclx, interval), 1000);
        }
    }

    // 停止抢课函数
    function stopSniper() {
        try {
            console.log('正在停止抢课...');
            // 清除定时器
            if (intervalId) {
                clearInterval(intervalId);
                intervalId = null;
            }

            // 清除刷新定时器
            if (refreshTimeout) {
                clearTimeout(refreshTimeout);
                refreshTimeout = null;
            }

            // 清除自动启动标记
            const config = getConfig();
            if (config) {
                saveConfig(config.kcdm, config.kclx, config.interval, false);
            }

            // 启用开始按钮，禁用停止按钮
            const startBtn = document.getElementById('startBtn');
            const stopBtn = document.getElementById('stopBtn');
            if (startBtn && stopBtn) {
                startBtn.disabled = false;
                stopBtn.disabled = true;
            }

            const resultArea = document.getElementById('resultArea');
            const time = new Date().toLocaleTimeString();
            resultArea.innerHTML = `${time}: 已停止抢课<br>` + resultArea.innerHTML;
            
            console.log('抢课已停止');
        } catch (error) {
            console.error('停止失败:', error);
        }
    }

    // 在页面关闭或刷新前停止抢课
    window.addEventListener('beforeunload', function() {
        // if (intervalId || refreshTimeout) {
        //     stopSniper();
        // }
    });
})(); 