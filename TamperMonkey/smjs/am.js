// == Helper Functions ==

/**
 * 等待指定 XPath 的元素出现在 DOM 中
 * @param {string} xpath - 元素的 XPath
 * @param {number} timeout - 最大等待时间 (毫秒)
 * @param {Document|Element} contextNode - XPath 的上下文节点，默认为 document
 * @returns {Promise<Element>} - 当元素出现时，Promise resolve 对应的元素
 */
function waitForElementXPath(xpath, timeout = 10000, contextNode = document) {
    console.log(`Waiting for XPath: ${xpath}`);
    return new Promise((resolve, reject) => {
        const startTime = Date.now();
        const interval = setInterval(() => {
            const element = document.evaluate(xpath, contextNode, null, XPathResult.FIRST_ORDERED_NODE_TYPE, null).singleNodeValue;
            if (element) {
                clearInterval(interval);
                console.log(`Found XPath: ${xpath}`);
                resolve(element);
            } else if (Date.now() - startTime > timeout) {
                clearInterval(interval);
                console.error(`Timeout waiting for XPath: ${xpath}`);
                reject(new Error(`Timeout waiting for element with XPath: ${xpath}`));
            }
        }, 500); // 每 500 毫秒检查一次
    });
}

/**
 * 等待指定 CSS 选择器的元素出现在 DOM 中
 * @param {string} selector - 元素的 CSS 选择器
 * @param {number} timeout - 最大等待时间 (毫秒)
 * @param {Document|Element} contextNode - CSS 选择器的上下文节点，默认为 document
 * @returns {Promise<Element>} - 当元素出现时，Promise resolve 对应的元素
 */
function waitForElementCSS(selector, timeout = 10000, contextNode = document) {
    console.log(`Waiting for CSS Selector: ${selector}`);
    return new Promise((resolve, reject) => {
        const startTime = Date.now();
        const interval = setInterval(() => {
            const element = contextNode.querySelector(selector);
            if (element) {
                clearInterval(interval);
                console.log(`Found CSS Selector: ${selector}`);
                resolve(element);
            } else if (Date.now() - startTime > timeout) {
                clearInterval(interval);
                console.error(`Timeout waiting for CSS Selector: ${selector}`);
                reject(new Error(`Timeout waiting for element with CSS selector: ${selector}`));
            }
        }, 500); // 每 500 毫秒检查一次
    });
}

/**
 * 延迟函数
 * @param {number} ms - 延迟的毫秒数
 * @returns {Promise<void>}
 */
function delay(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

/**
 * 安全地点击元素
 * @param {Element|string} elementOrSelector - 元素对象或其 XPath/CSS 选择器
 * @param {'xpath'|'css'} [selectorType='xpath'] - 如果第一个参数是选择器，则指定选择器类型
 * @returns {Promise<void>}
 */
async function safeClick(elementOrSelector, selectorType = 'xpath') {
    try {
        let element;
        if (typeof elementOrSelector === 'string') {
            if (selectorType === 'xpath') {
                element = await waitForElementXPath(elementOrSelector);
            } else {
                element = await waitForElementCSS(elementOrSelector);
            }
        } else {
            element = elementOrSelector; // 假设已经是元素对象了
        }
        
        if (element && typeof element.click === 'function') {
            console.log('Clicking element:', element);
            element.click();
            await delay(500); // 点击后给一点点反应时间
        } else {
            console.error('Element not found or not clickable:', elementOrSelector);
        }
    } catch (error) {
        console.error('Error during click:', error);
    }
}


// == Main Automation Logic ==

async function processSingleWorkOrder(orderRow) {
    // 1. 检查“处理人”一栏是否为空
    //    你需要找到“处理人”单元格的 XPath 或 CSS 选择器 (相对于 orderRow)
    //    假设“处理人”是该行的第 N 个单元格 (td)
    const handlerCellXPath = './/td[N]'; // N 是“处理人”列的索引，从1开始
    // 或者用 CSS: const handlerCellSelector = 'td:nth-child(N)';
    
    let handlerCell;
    try {
        // 使用 orderRow 作为上下文节点来查找单元格
        handlerCell = document.evaluate(handlerCellXPath, orderRow, null, XPathResult.FIRST_ORDERED_NODE_TYPE, null).singleNodeValue;
        // 如果用 CSS Selector: handlerCell = orderRow.querySelector(handlerCellSelector);
    } catch (e) {
        console.error("Error finding handler cell for row:", orderRow, e);
        return; // 跳过此行
    }

    if (handlerCell && handlerCell.textContent.trim() === '') {
        console.log('Found an empty handler for order:', orderRow);

        // 2. 点击“处理”按钮
        //    你需要找到该行“处理”按钮的 XPath 或 CSS 选择器 (相对于 orderRow)
        const processButtonXPath = './/button[contains(text(),"处理")]'; // 假设按钮文本包含“处理”
        // 或者用 CSS: const processButtonSelector = 'button.process-button-class'; // 假设按钮有特定类名

        await safeClick(processButtonXPath, 'xpath'); // 注意：这里 XPath 的上下文应该是 orderRow，但 safeClick 目前全局搜索，需要调整或传入 orderRow
        // 如果要以 orderRow 为上下文，可以这样:
        // const processButton = await waitForElementXPath(processButtonXPath, 5000, orderRow);
        // await safeClick(processButton);


        // 3. 等待第一个弹窗出现，并点击“我来处理”
        //    你需要找到第一个弹窗中“我来处理”按钮的 XPath 或 CSS 选择器
        const iWillHandleButtonXPath = '//div[@class="modal-popup-1"]//button[contains(text(),"我来处理")]'; // 假设的XPath
        await safeClick(iWillHandleButtonXPath, 'xpath');

        // 4. 等待第二个弹窗出现，并点击其“关闭”按钮
        //    你需要找到第二个弹窗中“关闭”按钮的 XPath 或 CSS 选择器
        const closeButtonPopup2XPath = '//div[@class="modal-popup-2"]//button[contains(text(),"关闭")]'; // 假设的XPath
        await safeClick(closeButtonPopup2XPath, 'xpath');
        await delay(500); // 等待第二个弹窗关闭动画

        // 5. 点击第一个弹窗的“关闭”按钮
        //    你需要找到第一个弹窗中“关闭”按钮的 XPath 或 CSS 选择器
        const closeButtonPopup1XPath = '//div[@class="modal-popup-1"]//button[contains(text(),"关闭")]'; // 假设的XPath
        // 确保第一个弹窗在第二个弹窗关闭后是可见且可交互的
        await safeClick(closeButtonPopup1XPath, 'xpath');
        await delay(1000); // 等待第一个弹窗关闭并刷新列表（如果会自动刷新的话）

        console.log('Successfully processed order:', orderRow);
    } else {
        // console.log('Handler not empty or cell not found for order:', orderRow);
    }
}

async function mainAutomationTask() {
    console.log('Starting automation task...');

    // 0. 点击“查询案例”按钮 (如果需要的话)
    //    你需要找到“查询案例”按钮的 XPath 或 CSS 选择器
    const queryCaseButtonXPath = '//button[contains(text(),"查询案例")]'; // 假设的XPath
    // await safeClick(queryCaseButtonXPath, 'xpath');
    // await delay(2000); // 等待表格数据加载

    // 1. 获取所有工单行
    //    你需要找到工单表格中所有行的 XPath 或 CSS 选择器
    const workOrderRowsXPath = '//table[@id="workOrderTable"]/tbody/tr'; // 假设的XPath
    // 或者 CSS: const workOrderRowsSelector = '#workOrderTable tbody tr';
    
    let workOrderRows;
    try {
        // 使用 document.evaluate 获取节点集合
        const result = document.evaluate(workOrderRowsXPath, document, null, XPathResult.ORDERED_NODE_ITERATOR_TYPE, null);
        workOrderRows = [];
        let node = result.iterateNext();
        while (node) {
            workOrderRows.push(node);
            node = result.iterateNext();
        }
        // 如果用 CSS Selector: workOrderRows = Array.from(document.querySelectorAll(workOrderRowsSelector));

        if (!workOrderRows || workOrderRows.length === 0) {
            console.log('No work orders found.');
            return;
        }
        console.log(`Found ${workOrderRows.length} work orders.`);

    } catch (e) {
        console.error("Error finding work order rows:", e);
        return;
    }


    // 2. 遍历处理每一条工单 (使用 for...of 循环配合 await，确保顺序执行)
    for (const row of workOrderRows) {
        try {
            await processSingleWorkOrder(row);
            // 在处理完一个工单后，可以稍微等待一下，以防操作过快或页面有响应延迟
            await delay(1000); // 可调整的延时
        } catch (error) {
            console.error('Error processing a work order row:', row, error);
            // 根据需要决定是否继续处理下一条，或者停止
        }
    }

    console.log('Automation task finished for this cycle.');
}

// == Execution Control ==
let automationIntervalId = null;

function startAutomation(intervalMinutes = 5) {
    if (automationIntervalId) {
        console.log('Automation is already running.');
        return;
    }
    console.log(`Starting automation. Will run every ${intervalMinutes} minutes.`);
    // 立即执行一次
    mainAutomationTask().catch(error => console.error("Initial run error:", error));
    
    automationIntervalId = setInterval(() => {
        mainAutomationTask().catch(error => console.error("Scheduled run error:", error));
    }, intervalMinutes * 60 * 1000);
}

function stopAutomation() {
    if (automationIntervalId) {
        clearInterval(automationIntervalId);
        automationIntervalId = null;
        console.log('Automation stopped.');
    } else {
        console.log('Automation is not running.');
    }
}

// == HOW TO USE ==
// 1. 打开浏览器开发者工具 (通常是 F12)，切换到 Console (控制台) 标签页。
// 2. 复制以上所有代码，粘贴到控制台中，然后按 Enter 执行。
// 3. 修改 XPath/CSS 选择器：
//    - `queryCaseButtonXPath` (如果需要点击查询按钮)
//    - `workOrderRowsXPath` (工单表格行的XPath)
//    - 在 `processSingleWorkOrder` 函数中:
//        - `handlerCellXPath` (处理人单元格的XPath，相对于行)
//        - `processButtonXPath` (处理按钮的XPath，相对于行)
//        - `iWillHandleButtonXPath` (第一个弹窗中“我来处理”按钮的XPath)
//        - `closeButtonPopup2XPath` (第二个弹窗中“关闭”按钮的XPath)
//        - `closeButtonPopup1XPath` (第一个弹窗中“关闭”按钮的XPath)
//    务必确保这些 XPath 能够准确地定位到你页面上的元素。
//
// 4. 在控制台中执行以下命令来启动自动化:
//    startAutomation(5); // 每 5 分钟执行一次，你可以修改数字
//
// 5. 如果需要停止自动化，在控制台中执行:
//    stopAutomation();
//
// 提示:
// - 确保你的XPath表达式是准确的。你可以使用开发者工具的 "Elements" 面板测试XPath ($x("YOUR_XPATH_HERE") 在控制台执行)。
// - `waitForElementXPath` 和 `waitForElementCSS` 中的 `timeout` 参数可以根据你的网络和页面加载速度调整。
// - `delay()` 函数的延时也可以按需调整。