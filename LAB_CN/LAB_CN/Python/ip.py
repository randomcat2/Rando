def get_ip_class(ip_address):
    first_octet = int(ip_address.split('.')[0])
    
    if 1 <= first_octet <= 126:
        return 'A'
    elif 128 <= first_octet <= 191:
        return 'B'
    elif 192 <= first_octet <= 223:
        return 'C'
    elif 224 <= first_octet <= 239:
        return 'D'
    elif 240 <= first_octet <= 255:
        return 'E'
    else:
        return 'Unknown'

def is_private(ip_address):
    first_octet = int(ip_address.split('.')[0])
    
    if first_octet == 10:
        return True
    elif first_octet == 172 and 16 <= int(ip_address.split('.')[1]) <= 31:
        return True
    elif first_octet == 192 and int(ip_address.split('.')[1]) == 168:
        return True
    else:
        return False

def main():
    ip_address = input("Enter IP address (xxx.xxx.xxx.xxx format): ")
    
    ip_class = get_ip_class(ip_address)
    print("IP Class:", ip_class)

    if is_private(ip_address):
        print("IP Type: Private")
    else:
        print("IP Type: Public")

if __name__ == "__main__":
    main()
