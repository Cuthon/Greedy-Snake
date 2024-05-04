# Greedy-Snake

## 基于easyX的贪吃蛇小游戏

### 环境配置(windows)

1. 在 https://jmeubank.github.io/tdm-gcc/download/ 下载并安装TDM-GCC，并勾选add to path  
2. 下载CMake，并在VScode配置好CMake  
3. 创建build目录，在build目录下：  
   ```powershell
   cmake ..
   cmake --build .
   ```

### 环境依赖

/lib目录下的libeasyx.a为easyX的静态库文件，/include/thirdpart目录下的.h文件为easyX的头文件，库文件必须是支持mingw编译器的版本  
easyX官网：https://easyx.cn/easyx
