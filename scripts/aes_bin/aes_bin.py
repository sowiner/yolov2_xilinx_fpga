from argparse import ArgumentParser
from aes import AES

nist_aes128_key = (0x2B7E1516, 0x28AED2A6, 0xABF71588, 0x09CF4F3C)
nist_aes256_key = (
    0x603DEB10,
    0x15CA71BE,
    0x2B73AEF0,
    0x857D7781,
    0x1F352C07,
    0x3B6108D7,
    0x2D9810A3,
    0x0914DFF4,
)


def read_binary_file(file_path):
    with open(file_path, "rb") as file:
        return file.read()


def write_binary_file(file_path, data):
    with open(file_path, "wb") as file:
        file.write(data)


def main(input_file, output_file, aes_type):
    key = nist_aes128_key if aes_type == "aes128" else nist_aes256_key

    # Read the binary file
    data = read_binary_file(input_file)

    # Encrypt the data
    a = AES()
    encrypted_data = a.aes_encipher_block(data, key)
    # Write the encrypted data to the new output file
    write_binary_file(output_file, encrypted_data)


def test_bin(input_file, output_file, aes_type):
    key = nist_aes128_key if aes_type == "aes128" else nist_aes256_key
    # Read the binary file
    idata = read_binary_file(input_file)
    odata = read_binary_file(output_file)

    a = AES()
    result = a.aes_decipher_block(key, odata)
    return a.check_block(result, idata)


if __name__ == "__main__":
    # if len(sys.argv) != 3:
    #     print(f"Usage: {sys.argv[0]} <input_file> <aes_type>")
    #     sys.exit(1)

    # input_file = sys.argv[1]
    # aes_type = sys.argv[2]

    # if aes_type not in ["aes128", "aes256"]:
    #     print("Error: aes_type must be 'aes128' or 'aes256'")
    #     sys.exit(1)
    parser = ArgumentParser()
    group = parser.add_mutually_exclusive_group()
    group.add_argument(
        "-c", "--cipher", action="store_true", required=True, help="加密檔案"
    )
    group.add_argument("-t", "--test", action="store_true", required=True, help="測試")
    parser.add_argument("input_file", type=str, help="輸入bin 檔案路徑")
    parser.add_argument("output_file", type=str, help="輸出bin 檔案路徑")
    parser.add_argument("aes_type", type=str, help="aes 類型")
args = parser.parse_args()
if args.cipher:
    main(args.input_file, args.output_file, args.aes_type)
elif args.test:
    test_bin(args.input_file, args.output_file, args.aes_type)
else:
    print("Error: aes_type must be 'aes128' or 'aes256'")
