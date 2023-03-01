# ComputerNetwork

## 소켓 프로그래밍 1 (TCP server, client) 

1. Server에서는 client에서 전송한 데이터를 화면에 출력시킨다.

2. client에서는 server와 connection establish를 한 다음, 즉시 10 바이트 데이터 3개를 3번의 send() 함수를 이용하여 server에 전송한다. (예를 들면 0123456789, ABCDEFGHIJ, KLMNOPQRST)

3. 그 후 터미널로부터 입력된 데이터를 server에 전송함. (한 라인의 데이터를 받아서 전송함.) 사용자가 ‘q’를 입력하면 client 프로그램을 종료시킴.

4. Server는 client 와 connection establish를 한 다음, 5초 동안 sleep 한 다음, 최대 buffer 크기가 100 바이트인 버퍼를 이용하여 읽은 다음, 읽은 데이터를 화면에 출력시킴. (recv() 이용하여 데이터 읽음.) 동일한 형태로 (최대 buffer 크기가 100 바이트인 버퍼를 이용하여 읽음.)

## 소켓 프로그래밍 2 (TCP server, client) 

1. 전송할 파일의 이름을 서버에게 알려준다.

2. 파일의 내용을 전송한다. (이때 서버에서는 전송된 파일 이름으로 해당 파일을 저장하여야 한다.)

3. 파일 이름을 전송한 다음, 지연 없이 즉시 파일내용을 전송하여야 한다(ACK사용금지).

4. 서버는 iterative 형태여야 한다.

5. 시간지연 코드를 사용하면 안된다.

6. 파일은 아스키, 바이너리 모두 지원해야한다.

## 소켓 프로그래밍 3 (TCP server, client) 


## SMTP_C 

SMTP 클라이언트 프로그램을 TCP 소켓을 이용해 C언어로 구현한 것입니다.

구조: SMTP_CLIENT -> 개인 SMTP 서버 -> 네이버 
## SMTP_CPP

SMTP 클라이언트 프로그램을 C++언어로 구현한 것입니다. 위 코드를 리팩토링해 좀 더 깔끔하게 만들었습니다.
<img width="1194" alt="스크린샷 2023-03-01 오후 8 59 11" src="https://user-images.githubusercontent.com/87226129/222134123-ed8d3937-ffe7-4cdb-b44a-576029669a79.png">

<img width="1447" alt="스크린샷 2023-03-01 오후 9 18 25" src="https://user-images.githubusercontent.com/87226129/222137407-efcddb98-9056-4586-8f1a-e317e4f9707d.png">



