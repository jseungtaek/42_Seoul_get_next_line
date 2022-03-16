# 42_Seoul_get_next_line
## 42_Seoul second assignment get next line

# Get_Next_line

![Screen Shot 2022-03-07 at 5.03.33 PM.png](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/80cee542-8813-4668-a827-2c9b5175a62b/Screen_Shot_2022-03-07_at_5.03.33_PM.png)

1. file descriptor
    - 운영체제가 파일 또는 하드웨어와 통신을 하기 위해 부여하는 숫자
    - 파일 디스크럽터(fd)는 0,1,2 순으로 숫자를 부여하며 0,1,2는 이미 사용중이므로 3부터 fd를 부여
        - 0 : 표준 입력
        - 1 : 표준 출력
        - 2 : 표준 에러
    - open() 함수는 파일을 열고 파일 디스크립터 값을 반환한다. 그 값을 이용하여 이후에도 계속해서 열었던 파일에 접근 가능
    - 프로세스가 실행 중에 파일을 open 하면 커널은 해당 프로세스의 fd 숫자 중에 사용하지 않는 가장 작은 값을 할당 해준다. 그 후 프로세스가 열려있는 파일에 시스템 콜을 이용해서 접근 할 때, fd 값을 이용해 파일을 지칭 할 수 있다.
    - 0 ~ OPEN_MAX(fd의 최대값) 까지의 값을 가질 수 있다. OPEN_MAX는 단일 프로그램에 허용되는 최대 열린 파일 수를 정의하는 상수
2. read() 함수
    
    ```c
    size_t read(int fd, void *buf, size_t bytes)
    ```
    
    - 인자로 받은 bytes의 수 만큼 fd를 읽어 buffer에 저장하는 함수
    - 읽어 온 바이트 수를 반환하며, 실패시 -1 반환
    - 파일을 끝까지 읽었다면, 다음 번에는 더 이상 읽을 바이트가 없기 때문에 0 반환
    - 1은 한 줄이 읽힘을 의미
3. BUFFER_SZIE
    - 한번에 읽을 수 있는 BUFFER_SIZE 설정 가능
    - BUFFER overflow 쓰려는 버퍼크기를 넘어서서 요청하면 중요한 내용을 읽어가거나 옆의 메모리가 오염될 수 있다.
        - 오버플로우를 피하기 위해 heap 영역에 할당
            - 동적할당을 이용하는 이유
    
    |  | 설명 | 크기 | 할당과 접근 속도 |
    | --- | --- | --- | --- |
    | 스택세그먼트
    (=콜스택) | 스택 자료구조로 구현되어 있다. (함수가 호출되고 종료될 때 호출됐던 곳으로 돌아가는 방식) | 메모리 영역의 크기가 고정되어 있다. 크기가 비교적 작다. (windows에서는 1MB) | 할당이 비교적 빠르다. 변수를 통해 직접 접근할 수 있다. |
    | 힙세그먼트 | 동적메모리할당. 주소가 순차적으로 할당되지는 않는다. 메모리의 주소는 포인터에 저장해서 사용한다. | 큰 메모리 풀이다. (일반적으로 2GB) | 할당이 비교적 느리다. 포인터를 통해 접근하므로, 역참조해야 해서 좀더 느리다. |
    - 출처
        
        [https://probable-perch-892.notion.site/64fd6eafcb1748b4bb9a7529d00d37cb#885971f19635431a9a80a45d393860c1](https://www.notion.so/get_next_line-Defence-64fd6eafcb1748b4bb9a7529d00d37cb)
        
4. OPEN_MAX
    - fd(file descriptor)의 최대값
    - OPEN_MAX는 단일 프로그램에 허용되는 최대 열린 파일 수를 정의하는 “상수”
    - Unix 시스템에서 C Language의 OPEN_MAX는 limits.h에 정의되어 있음
    
    ```c
    // FIND OPEN_MAX
    getconf OPEN_MAX
    
    //클러스터 mac은 256
    ```
    
5. static variable
    - 변수 선언 시 static 키워드를 붙여 선언
    
    ```c
    static int anyword
    ```
    
    - 메모리의 데이터 영역에 저장되어 프로그램이 종료될 때까지 남아있는 변수
    - 함수를 벗어나도 해당 변수는 사라지지 않고 계속 유지, but 함수 내부에서 선언되었다면, 다른 함수에서는 이 값을 참조할 수 없다. 함수의 시작이 아닌 프로그램의 시작 시 할당이 되며, 프로그램이 종료될 때 해제된다.
    - 함수 내에서 초기화 시 프로그램이 시작될 때 변수를 초기화, 함수가 호출 시에는 변수 초기화 X
        - 여러 번 함수를 실행 하더라도 변수가 또 초기화 되진 않음
    - 정적 변수는 초기값을 지정하지 않으면 0으로 자동 초기화
    - 이번 gnl project 에서는 다음 line을 읽을 시작 주소를 계속 저장할 수 있도록 backup buffer를 만들어 static 변수로 선언해야 된다.
6. gcc -d flag
    - 외부에서 #define을 정의
    - 위 프로젝트에서는 컴파일 시에 버퍼사이즈를 정의
    
    ```c
    gcc -Wall -Wextra -Werror -D BUFFER_SIZE=/*(SIZE)*/ get_next_line.c get_next_line_utlis.c get_next_line.h 
    ```
    
7. EOF
    - EOF(end of file) : 파일의 끝, 데이터 소스로부터 더 이상 읽을 수 있는 데이터가 없음을 나타낸다

 8. 댕글링 포인터

- 포인터가 여전히 해제된 메모리 영역을 가리키고 있는 것
    - 메모리 해제 후 포인터를 NULL로 설정
1. const char / char const
    - const char * 상수형 문자에 대한 포인터, 포인터가 가리키는 변수의 값을 바꿀 수 없음
    - char const * 문자에 대한 상수형 포인터, 포인터 값을 바꿀 수 없음
