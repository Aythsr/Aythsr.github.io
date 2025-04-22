from out_ip import process_pcap
import sys


if __name__ == "__main__":
    for i in range(1, 5):
        for j in range(1, 8):
            input_file = f"test-icccn{i}/host {j}-{j-1}-0.pcap"
            output_file = f"iccc{i}/host-{j}.pcap"
            process_pcap(input_file, output_file)
            print(f"Processed {input_file} -> {output_file}")
    pass