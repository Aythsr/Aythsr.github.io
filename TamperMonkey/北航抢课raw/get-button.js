// ==UserScript==
// @name         链接点击监听器
// @namespace    http://tampermonkey.net/
// @version      0.1
// @description  监听页面上所有<a>标签的点击事件并获取信息
// @author       Your name
// @match        *://*/*
// @grant        none
// @run-at       document-start

// ==/UserScript==

(function() {
    'use strict';

    // 添加点击事件监听器到document
    document.addEventListener('click', function(event) {
        // 检查点击的元素是否是<a>标签
        let clickedElement = event.target.closest('a');
        
        if (clickedElement) {
            // 获取<a>标签的所有信息
            // "<a role="xk" href="javascript:void(0);" class="zeromodal-btn zeromodal-btn-primary xkbtn" role-dxzwid="" role-kzwid="" role-kcms="D061041011-机器学习（01）" role-val="20242-010600-D061041011-1735543436340">选课</a>"
            // 获取其 role-kcms 与 role-val
            const roleKcms = clickedElement.getAttribute('role-kcms') || '无课程信息';
            const roleVal = clickedElement.getAttribute('role-val') || '无选课值';
            const rolelx = clickedElement.getAttribute('role') || null;
            if (rolelx) {
                console.log('课程信息:', roleKcms);
                console.log('选课值:', roleVal);
            }
        }
    });
})();
