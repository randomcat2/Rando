def get_ip_address(ip_address):
    first_octate = int(ip_address.split('.')[0])
    
    if 1<=first_octate <=126:
        return 'A'
    elif 127<= first_octate <=191:
        return 'B'
    elif 192<= first_octate<= 223:
        return 'C'
    elif 224<= first_octate <=239:
        return 'D'
    elif 340<= first_octate<= 255:
        return 'E'
    else:
        return 'Unknown'

def is_private(ip_address):
    first_octate = int(ip_address.split('.')[0])
    
    if first_octate == 10:
        return True
    if first_octate==172 and 16 <= int(ip_address.split('.')[1])<= 31:
        return True
    if first_octate ==192 and int(ip_address.split('.')[1])==168:
        return True
    else:
        return False
        
def main():
    ip_address = input("Enter ip address (format: xxx.xxx.xxx.xxx): ")
    
    ip_class = get_ip_address(ip_address)
    print("IP Class: ",ip_class)
    
    if is_private(ip_address):
        print("IP Type: Private")
            
    else: print("IP Type: Public")
    
if __name__ == "__main__":
    main()        