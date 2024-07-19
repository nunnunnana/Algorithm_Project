# Algorithm_Visualization_Project

## 프로젝트 소개
### 언리얼 엔진을 활용한 알고리즘 시각화 프로젝트

![Algorithm_Intro](https://github.com/nunnunnana/Algorithm_Project/assets/99165741/99f065d7-c59d-4659-a3f8-1818a9389791)


### [시연 영상](https://youtu.be/0EBkD9h4xiw)

## 조작법
마우스 좌클릭으로 버튼 선택
화면 우측 하단에 버튼을 클릭해 실행할 알고리즘 선택

***

## 1. 스택, 큐

### 시연 영상
>Stack

![Stack_Visualization](https://github.com/nunnunnana/Algorithm_Project/assets/99165741/4ee3d420-7d2c-47dc-85ed-bb43d352efe1)

>Queue

![Queue_Visualization](https://github.com/nunnunnana/Algorithm_Project/assets/99165741/e57d612a-057b-4d88-b5fa-642b894ff5f4)

## 주요기능

>### 액터 생성
- 메시, Material 에셋을 찾아 액터 기본 설정
https://github.com/nunnunnana/Algorithm_Visualization_Project/blob/d3e971d6972a6ce5b3ad0173649aaa640cf49a1b/Source/Algorithm_Project/StackQueue.cpp#L11-L29

- 액터 생성 및 제거 함수
- 타임라인을 이용해 액터를 움직일 예정으로 SetMobility를 Movable로 설정
https://github.com/nunnunnana/Algorithm_Visualization_Project/blob/f509ef499e237820fa9bfd7293c67805698d9c2c/Source/Algorithm_Project/StackQueue.cpp#L346-L366

>### 스택 Push, Pop
- 액터를 처음 생성할 때와 추가로 생성할 때의 위치를 다르게하기 위해서 height 값을 받아서 위치 값 설정
- Timeline을 실행하기 전 현재위치(currentZLocation)와 목표위치(targetZLocation)를 각각 설정
- Top에 있는 액터의 색상은 빨간색으로 설정
https://github.com/nunnunnana/Algorithm_Visualization_Project/blob/0baa2273f5c702c14ec644768e0b873fdf8e538c/Source/Algorithm_Project/StackQueue.cpp#L163-L194

- 큐 Enqueue, Dequeue도 동일하게 작성
https://github.com/nunnunnana/Algorithm_Visualization_Project/blob/64354e17d93ad4be1655343ae680173adbd638c3/Source/Algorithm_Project/StackQueue.cpp#L266-L286

>### Timeline
- 생성된 액터가 쌓이고 빠져나가는 느낌을 주기위해 Timeline을 이용해 액터 위치값 변경
- 타임라인에 사용할 Curve 생성 및 설정
<img src="https://github.com/nunnunnana/Algorithm_Visualization_Project/assets/99165741/36e6e1d7-e3ef-403a-a35e-bdc85739ac88.png" width="500" height="300"/>

- 함수 바인드, 타임라인 Direction, Callback 함수 등등 타임라인 초기 설정
https://github.com/nunnunnana/Algorithm_Visualization_Project/blob/64354e17d93ad4be1655343ae680173adbd638c3/Source/Algorithm_Project/StackQueue.cpp#L42-L75

- 현재 위치에서 목표 위치로 Lerp하게 변경
- 큐에서는 Y축으로 변경
https://github.com/nunnunnana/Algorithm_Visualization_Project/blob/64354e17d93ad4be1655343ae680173adbd638c3/Source/Algorithm_Project/StackQueue.cpp#L146-L150

***

## 2. 정렬

### 시연 영상
>Selection sort

![Sort_Selection](https://github.com/nunnunnana/Algorithm_Visualization_Project/assets/99165741/49fb040d-68f4-43b4-b134-9577e3eb3cdc)

>Injection sort

![Sort_Injection](https://github.com/nunnunnana/Algorithm_Visualization_Project/assets/99165741/2aed695b-6434-457f-90a0-8286ed6d0e9c)

>Bubble sort

![Sort_Bubble](https://github.com/nunnunnana/Algorithm_Visualization_Project/assets/99165741/ec34b223-cba4-4095-8f48-01a726e69cb3)

>Merge sort

![Sort_Merge](https://github.com/nunnunnana/Algorithm_Visualization_Project/assets/99165741/9d94ba18-4ef7-4e29-8f84-62aec3403ad4)

>Quick sort

![Sort_Quick](https://github.com/nunnunnana/Algorithm_Visualization_Project/assets/99165741/652a1e3d-eb50-4e6b-b771-042d8b64e4f8)

## 주요기능

>### 정렬 해야할 블록 생성
- BeginPlay에서 Size 만큼 SpawnActor 함수 호출
- actorIndex 값 만큼 Y 축 설정
https://github.com/nunnunnana/Algorithm_Visualization_Project/blob/64354e17d93ad4be1655343ae680173adbd638c3/Source/Algorithm_Project/SortActor.cpp#L53-L65

- 액터가 생성되면 index 값 만큼 Z축으로 액터 생성
https://github.com/nunnunnana/Algorithm_Visualization_Project/blob/64354e17d93ad4be1655343ae680173adbd638c3/Source/Algorithm_Project/SortActorMesh.cpp#L51-L60

>### 블록 Shuffle

![Sort_Shuffle](https://github.com/nunnunnana/Algorithm_Visualization_Project/assets/99165741/bdd8a72c-09f9-414b-9b44-d9e9ebd95638)

- arrTarget 배열을 랜덤하게 섞고 배열의 인덱스 값에 따라서 Location 설정해주는 함수 호출
https://github.com/nunnunnana/Algorithm_Visualization_Project/blob/58009575aba7c1c1d3c92725fe703197a3b60195/Source/Algorithm_Project/SortActor.cpp#L67-L93

>### 선택 정렬
- 가장 낮은 Index를 찾을 때 현재의 Index는 파란색, 가장 낮은 Index는 빨간색으로 설정
https://github.com/nunnunnana/Algorithm_Visualization_Project/blob/6a9059541bdf2af3b704d8438ad7d9a481015548/Source/Algorithm_Project/SortActor.cpp#L120-L164

>### 삽입 정렬
- 원소 비교 후 색상 설정할 때 각각 하얀색, 파란색으로 설정
https://github.com/nunnunnana/Algorithm_Visualization_Project/blob/6a9059541bdf2af3b704d8438ad7d9a481015548/Source/Algorithm_Project/SortActor.cpp#L177-L208

>### 버블 정렬
- Index를 비교할 때 Swap이 일어나면 빨간색, Swap을 하지 않으면 파란색으로 표시
https://github.com/nunnunnana/Algorithm_Visualization_Project/blob/6a9059541bdf2af3b704d8438ad7d9a481015548/Source/Algorithm_Project/SortActor.cpp#L222-L250

>### 합병 정렬
- 합병 정렬은 다른 정렬과 다르게 coroutine 사용
https://github.com/nunnunnana/Algorithm_Visualization_Project/blob/6a9059541bdf2af3b704d8438ad7d9a481015548/Source/Algorithm_Project/SortActor.cpp#L272-L318

>### 퀵 정렬
- 합병 정렬과 마찬가지로 coroutine 사용
https://github.com/nunnunnana/Algorithm_Visualization_Project/blob/6a9059541bdf2af3b704d8438ad7d9a481015548/Source/Algorithm_Project/SortActor.cpp#L330-L382

***

## 3. 탐색

### 시연 영상
>BFS

![Search_BFS](https://github.com/user-attachments/assets/c66ea4f1-1852-41ee-8e2f-aae62c53b7a7)

>DFS

![Search_DFS](https://github.com/user-attachments/assets/33a6959c-1d6e-4154-8ea7-9ed229f8df58)


>Dijkstra

![Search_Dijkstra](https://github.com/user-attachments/assets/7c823f16-4cd0-43af-b99f-1ac39fc3bf82)


>A*

![Search_AStar](https://github.com/user-attachments/assets/57decd59-eccb-48f8-837c-6cd8c96db98f)

## 주요기능

>### 미로 생성 및 Reset

![Search_Reset](https://github.com/user-attachments/assets/35d1111a-f8b8-471b-bd6e-c1bd03f81e7f)

- height와 width 값을 받아 각각 높이와 너비 설정, 액터간 간격은 100
- 벽은 랜덤하게 distribution 값에 따라 생성
https://github.com/nunnunnana/Algorithm_Visualization_Project/blob/6a9059541bdf2af3b704d8438ad7d9a481015548/Source/Algorithm_Project/Search.cpp#L33-L92

>### BFS
- 현재 Point를 기준으로 FindNeighborCell 함수를 통해 다음 방문할 Point들을 배열에 Add 후 첫 번째 원소부터 하나씩 빼서 탐색
https://github.com/nunnunnana/Algorithm_Visualization_Project/blob/e9e09c791580a60cf0b091155b4c489e9c4b9577/Source/Algorithm_Project/Search.cpp#L104-L155

>### DFS
- 상하좌우 중 방문해야할 Point가 있으면 랜덤으로 하나 정해서 Next Cell 설정 후 색상 변경 
https://github.com/nunnunnana/Algorithm_Visualization_Project/blob/843b41da9aad1a6ac788eb9465376c395740850a/Source/Algorithm_Project/Search.cpp#L157-L225

>### Dijkstra
- 기존 Dijkstra는 다음 노드로 가는 비용이 노드마다 다르지만 해당 알고리즘에서는 비용을 1로 산정한 뒤 시작 포인트에서 현재 Point까지의 비용을 표시하는 방법으로 수정
- BFS와 유사하게 탐색하지만 목표지점에 도달하면 시작지점으로 돌아가면서 최단 경로를 표시
https://github.com/nunnunnana/Algorithm_Visualization_Project/blob/843b41da9aad1a6ac788eb9465376c395740850a/Source/Algorithm_Project/Search.cpp#L227-L281

>### A*
- A* 알고리즘을 시작하면 각 Point마다 시작지점부터 현재 Point까지의 거리를 g, 현재 Point에서 목표지점까지의 거리를 h로 표시하도록 indicator 추가
- 두 지점 사이의 맨해튼 거리를 계산하는 함수를 호출해 다음 Point 설정하면서 목표지점에 도달하면 시작지점으로 돌아가면서 최단 경로를 표시
https://github.com/nunnunnana/Algorithm_Visualization_Project/blob/843b41da9aad1a6ac788eb9465376c395740850a/Source/Algorithm_Project/Search.cpp#L283-L369
