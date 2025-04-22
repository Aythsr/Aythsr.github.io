from scapy.all import Packet, rdpcap, wrpcap
from scapy.layers.inet import IP, Ether
from scapy.layers.ppp import PPP

def remove_single_ip_layer(pkt : Packet):
    # 仅移除最外层IP头，保留内层协议（如TCP/UDP或嵌套IP）
    if IP in pkt:
        # 提取IP层载荷（如TCP、UDP或内层IP）
        payload = pkt[IP].payload
        # 记录IP头的长度，通常为20字节(如无选项字段)
        ip_header_len = pkt[IP].ihl * 4
        
        # 重组包：保留原始链路层（如Ethernet），附加IP载荷
        new_pkt = pkt.copy()
        del new_pkt[IP]
        new_pkt.add_payload(payload)
        
        # 如果存在以太网帧，调整其长度信息
        if Ether in new_pkt:
            # Scapy通常会自动调整长度，但我们可以确保它正确处理
            new_pkt = Ether(bytes(new_pkt))
        
        # 如果存在PPP协议，也需要调整其长度
        if PPP in new_pkt:
            # 重新构建PPP包以更新长度字段
            new_pkt = PPP(bytes(new_pkt))
        
        return new_pkt
    else:
        return pkt  # 非IP包直接保留

def process_pcap(input_file, output_file):
    packets = rdpcap(input_file)
    processed = [remove_single_ip_layer(pkt) for pkt in packets]
    wrpcap(output_file, processed)

if __name__ == "__main__":
    # import sys
    # if len(sys.argv) != 3:
    #     print("Usage: python strip_ip.py input.pcap output.pcap")
    #     sys.exit(1)
    process_pcap("/Users/aythsr/Development/ShiningXiao/py_pcap/ns3-test-host1-0-0.pcap", 
                 "/Users/aythsr/Development/ShiningXiao/py_pcap/ns3-host1.pcap")
    process_pcap("/Users/aythsr/Development/ShiningXiao/py_pcap/ns3-test-host2-1-0.pcap", 
                 "/Users/aythsr/Development/ShiningXiao/py_pcap/ns3-host2.pcap")