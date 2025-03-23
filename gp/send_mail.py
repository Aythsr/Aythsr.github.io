import smtplib
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
from email.mime.application import MIMEApplication
from email.header import Header
import os
import time
from datetime import datetime
sender = "aythsr@qq.com"
receiver = "zhilinxiao@foxmail.com"
password = "psafrjcehomjbjgf"

def send_email_outlook(subject, body, attachments=None):
    """
    使用 QQ 服务器发送邮件
    
    参数:
        subject (str): 邮件主题
        body (str): 邮件正文
        attachments (list, optional): 附件文件路径列表，默认为None
    
    返回:
        bool: 发送成功返回True，否则返回False
    """
    global sender, receiver, password
    # QQ SMTP服务器配置
    smtp_server = "smtp.qq.com"
    smtp_port = 587
    
    # 创建邮件对象
    msg = MIMEMultipart()
    msg['From'] = sender
    
    # 处理收件人，可以是单个邮箱或邮箱列表
    if isinstance(receiver, list):
        msg['To'] = ', '.join(receiver)
        receiver_list = receiver
    else:
        msg['To'] = receiver
        receiver_list = [receiver]  # 转换为列表，便于后续处理
    
    # 设置邮件主题
    msg['Subject'] = Header(subject, 'utf-8')
    
    # 添加邮件正文
    msg.attach(MIMEText(body, 'plain', 'utf-8'))
    
    # 添加附件
    if attachments:
        for file_path in attachments:
            if os.path.exists(file_path):
                with open(file_path, 'rb') as f:
                    attachment = MIMEApplication(f.read())
                    attachment.add_header('Content-Disposition', 'attachment', 
                                         filename=Header(os.path.basename(file_path), 'utf-8').encode())
                    msg.attach(attachment)
    
    try:
        # 连接到服务器
        server = smtplib.SMTP(smtp_server, smtp_port)
        server.starttls()  # 启用TLS加密
        server.login(sender, password)
        
        # 发送邮件
        server.sendmail(sender, receiver_list, msg.as_string())
        server.quit()
        # print("邮件发送成功！")
        return True
    except Exception as e:
        # print(f"邮件发送失败: {str(e)}")
        return False

def send_GLOD_price(price : float, up: bool = False):
    # 获取当前日期时间 yyyy-mm-dd HH:MM:SS
    date_time = datetime.now().strftime("%m-%d %H:%M:%S")
    # print(date_time)
    subject = f"{'⬆️' if up else '⬇️'} {price:.2f} |金价|{date_time}"
    body = f"<h1>当前金价: {price:.8f} 人民币/克</h1>"
    send_email_outlook(subject, body)

# 使用示例
if __name__ == "__main__":
    import get_data
    price = get_data.get_GLOD_price()
    send_GLOD_price(price)