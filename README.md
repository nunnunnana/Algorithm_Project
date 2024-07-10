# Algorithm_Visualization_Project

# 프로젝트 소개
### 언리얼 엔진을 활용한 알고리즘 시각화 프로젝트

![Algorithm_Intro](https://github.com/nunnunnana/Algorithm_Project/assets/99165741/99f065d7-c59d-4659-a3f8-1818a9389791)


### [시연 영상](https://youtu.be/QfFVwr08LmE)

# 조작법
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

### 액터 생성
- 메시, Material 에셋을 찾아 액터 기본 설정
https://github.com/nunnunnana/Algorithm_Visualization_Project/blob/d3e971d6972a6ce5b3ad0173649aaa640cf49a1b/Source/Algorithm_Project/StackQueue.cpp#L11-L29


- 액터 생성 및 제거 함수
- 타임라인을 이용해 액터를 움직일 예정으로 SetMobility를 Movable로 설정
https://github.com/nunnunnana/Algorithm_Visualization_Project/blob/f509ef499e237820fa9bfd7293c67805698d9c2c/Source/Algorithm_Project/StackQueue.cpp#L346-L366

### 스택 Push, Pop
- 액터를 처음 생성할 때와 추가로 생성할 때의 위치를 다르게하기 위해서 height 값을 받아서 위치 값 설정
- Timeline을 실행하기 전 현재위치(currentZLocation)와 목표위치(targetZLocation)를 각각 설정
- Top에 있는 액터의 색상은 빨간색으로 설정
https://github.com/nunnunnana/Algorithm_Visualization_Project/blob/0baa2273f5c702c14ec644768e0b873fdf8e538c/Source/Algorithm_Project/StackQueue.cpp#L163-L194

### 큐 Enqueue, Dequeue
- 액터를 처음 생성할 때와 추가로 생성할 때의 위치를 다르게하기 위해서 height 값을 받아서 위치 값 설정
- Timeline을 실행하기 전 현재위치(currentZLocation)와 목표위치(targetZLocation)를 각각 설정
- Top에 있는 액터의 색상은 빨간색으로 설정
https://github.com/nunnunnana/Algorithm_Visualization_Project/blob/0baa2273f5c702c14ec644768e0b873fdf8e538c/Source/Algorithm_Project/StackQueue.cpp#L266-L277
https://github.com/nunnunnana/Algorithm_Visualization_Project/blob/0baa2273f5c702c14ec644768e0b873fdf8e538c/Source/Algorithm_Project/StackQueue.cpp#L286-L293

