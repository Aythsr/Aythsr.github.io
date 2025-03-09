// ==UserScript==
// @name         buaa
// @namespace    https://www.wanghaiyang.site
// @version      0.1
// @description  拦截POST请求并显示bjdm和lx参数
// @author       王海洋
// @match        https://yjsxk.buaa.edu.cn/*
// @grant        none
// ==/UserScript==

(function() {
    'use strict';

    // 修改创建面板函数
    function createPanel() {
        const panel = document.createElement('div');
        panel.style.cssText = `
            position: fixed;
            top: 20px;
            right: 20px;
            padding: 15px;
            background: white;
            border: 1px solid #ccc;
            border-radius: 8px;
            z-index: 9999;
            box-shadow: 0 4px 12px rgba(0,0,0,0.15);
            font-family: Arial, sans-serif;
        `;

        // 创建表格
        const table = document.createElement('table');
        table.style.cssText = `
            border-collapse: collapse;
            width: 100%;
            margin-bottom: 10px;
        `;

        const tilte = table.insertRow();
        const tiltet = tilte.insertCell();
        tiltet.textContent = '课程参数（手动选课后显示）'
        // 添加时间行
        const timeRow = table.insertRow();
        const timeLabel = timeRow.insertCell();
        const timeValue = timeRow.insertCell();
        timeLabel.textContent = '时间';
        timeValue.id = 'timeValue';
        
        // 添加课程代码行
        const bjdmRow = table.insertRow();
        const bjdmLabel = bjdmRow.insertCell();
        const bjdmValue = bjdmRow.insertCell();
        bjdmLabel.textContent = '课程代码';
        bjdmValue.id = 'bjdmValue';
        
        // 添加类型行
        const lxRow = table.insertRow();
        const lxLabel = lxRow.insertCell();
        const lxValue = lxRow.insertCell();
        lxLabel.textContent = '类型';
        lxValue.id = 'lxValue';

        // 设置单元格样式
        const cells = table.getElementsByTagName('td');
        for (let cell of cells) {
            cell.style.cssText = `
                padding: 8px;
                border-bottom: 1px solid #eee;
            `;
        }

        // 设置值单元格的特殊样式
        [timeValue, bjdmValue, lxValue].forEach(cell => {
            cell.style.cssText += `
                cursor: pointer;
                color: #1890ff;
                user-select: all;
                text-align: right;
            `;
            // 添加点击复制功能
            cell.addEventListener('click', function() {
                const text = this.textContent;
                navigator.clipboard.writeText(text).then(() => {
                    // 显示复制成功提示
                    const originalColor = this.style.color;
                    this.style.color = '#52c41a';
                    setTimeout(() => {
                        this.style.color = originalColor;
                    }, 500);
                });
            });
        });

        panel.appendChild(table);
        document.body.appendChild(panel);
        return { timeValue, bjdmValue, lxValue };
    }

    // 创建显示面板并获取引用
    const infoFields = createPanel();

    // 修改 XMLHttpRequest 拦截器
    const originalXHR = window.XMLHttpRequest;
    window.XMLHttpRequest = function() {
        const xhr = new originalXHR();
        const originalSend = xhr.send;

        xhr.send = function(body) {
            try {
                if (body) {
                    const params = new URLSearchParams(body);
                    const bjdm = params.get('bjdm');
                    const lx = params.get('lx');
                    
                    if (bjdm && lx) {
                        const time = new Date().toLocaleTimeString();
                        infoFields.timeValue.textContent = time;
                        infoFields.bjdmValue.textContent = bjdm;
                        infoFields.lxValue.textContent = lx;
                    }
                }
            } catch (error) {
                console.error('解析请求参数时出错:', error);
            }
            
            return originalSend.apply(this, arguments);
        };

        return xhr;
    };

    // 修改 fetch 拦截器
    const originalFetch = window.fetch;
    window.fetch = async function(url, options) {
        if (options && options.body) {
            try {
                const params = new URLSearchParams(options.body);
                const bjdm = params.get('bjdm');
                const lx = params.get('lx');
                
                if (bjdm && lx) {
                    const time = new Date().toLocaleTimeString();
                    infoFields.timeValue.textContent = time;
                    infoFields.bjdmValue.textContent = bjdm;
                    infoFields.lxValue.textContent = lx;
                }
            } catch (error) {
                console.error('解析fetch请求参数时出错:', error);
            }
        }
        
        return originalFetch.apply(this, arguments);
    };
})();