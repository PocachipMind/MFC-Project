# 기능 정의
### 파워포인트처럼 뷰 화면 영역에 도형을 그릴 수 있는 편집기를 제작

- 네모, 원 등 기본적인 도형 편집
- 각 도형 간 Z-order 적용
- 도형 외곽선 및 브러시 옵션 제공
- 파일 저장하기, 불러오기 기능 제공

# 파일 형식 규정
- 도형의 종류는 열거형 상수로 규정
- 도형의 위치 및 크기는 좌상단 좌표 및 폭, 높이를 저장 (CPoint, CSize)
- Z-order는 파일에 저장된 순서를 그대로 적용 ( 가장 먼저 저장된 도형이 화면의 맨 위에 나오는 구조 )
- MFC 직렬화 기능은 사용하지 않음

# 도형 그리기 및 이동
- 최초 도형을 그려 넣을 때는 툴바에서 선택한 도형 형식 및 색상을 반영해 추가
- 도형이 추가될 위치 및 크기는 사용자의 마우스 입력으로 결정
- 이미 그려져 있는 도형 중 하나를 선택하면 Z-order를 최상위로 변경하고 이동

# 더블 버퍼링 적용 및 도형 속성 변경
- 화면 렌더링 후 윈도우 크기 조절 시 깜빡이는 현상이 나타나지 않도록 반드시 더블 버퍼링 기능 적용
- 특정 도형을 선택한 후 속성을 변경했을 때 즉시 반영 ( 색상, 크기, 폭과 높이 등 )


![image](https://github.com/user-attachments/assets/5f32fe8d-1c52-415e-8828-eb36cc0dea32)
