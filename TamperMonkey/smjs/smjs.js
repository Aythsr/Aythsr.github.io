(function() {
    const $x = window.$x;
    let waittime = 1000;
    
    function sleep(ms) {
        return new Promise(resolve => setTimeout(resolve, ms));
    }
    async function waitForElement(selector) {
        while (true) {
            const element = $x(selector)[0];
            if (element) return element;
            await sleep(100);
        }
    }
    
    // 切换页面为40条每一页
    async function changepage() {
       $x("/html/body/div[1]/div/div/div[2]/section/div/div[1]/div/span[2]/div/div[1]/input")[0].click();
       let path = "/html/body/div[2]/div[1]/div[1]/ul/li[4]";
       await waitForElement(path);
       $x(path)[0].click();
       return sleep(waittime);
    }
    
    async function start(ttime) {
        await changepage();
        let cntt = 0;
        while (true) {
            console.log("第" + cntt + "次循环");
            await sleep(1000)
            .then(
                () => { // 点击查询
                    $x("/html/body/div[1]/div/div/div[2]/section/div/section[1]/div/form/div/div[12]/div/button[1]")[0].click();
                    return sleep(waittime);
                }
            )
            .then( // 遍历每一个工单
                async () => {
                    var cnt = $x("/html/body/div[1]/div/div/div[2]/section/div/section[2]/div[2]/div[3]/table/tbody/tr").length;
                    console.log("当前工单数量: " + cnt);
                    for (let i = 1; i <= cnt; ++i) {
                        
                        let xpath = "/html/body/div[1]/div/div/div[2]/section/div/section[2]/div[2]/div[4]/div[2]/table/tbody/tr[" + i + "]/td[14]/div";
                        let name = $x(xpath)[0].textContent;
                        if (name != "") {
                            console.log("第" + i + "个工单已经处理");
                            continue;
                        } else {
                            console.log("第" + i + "个工单没有处理人，开始处理");
                            xpath = "/html/body/div[1]/div/div/div[2]/section/div/section[2]/div[2]/div[4]/div[2]/table/tbody/tr[" + i + "]/td[19]/div/button[1]";
                            console.log("点击第" + i + "个工单的处理按钮");
                            $x(xpath)[0].click();


                            xpath = "/html/body/div[1]/div/div/div[2]/section/div/div[5]/div[1]/div/div[3]/div/button[4]";
                            const wlcl = await waitForElement(xpath);
                            await sleep(500);
                            console.log("点击第" + i + "个工单的我来处理按钮");
                            wlcl.click();
                            

                            xpath = "/html/body/div[1]/div/div/div[2]/section/div/div[5]/div[5]/div/div[1]/button/i";
                            const guanbi = await waitForElement(xpath);
                            console.log("点击关闭按钮");
                            await sleep(500);

                            guanbi.click();

                            xpath = "/html/body/div[1]/div/div/div[2]/section/div/div[5]/div[1]/div/div[1]/button/i"
                            const guanbi2 = await waitForElement(xpath);
                            console.log("再次点击关闭按钮");
                            await sleep(500);

                            guanbi2.click();
                        }
                        // console.log("点击第" + i + "个工单");
                        await sleep(waittime);
                    }
                    return sleep(waittime);
                }
            )
            .then(
                () => {
                    console.log("OK");
                }
            );
            await sleep(ttime * 1000);
            cntt++;
        }
    }

    // 启动脚本
    start(25);

})();