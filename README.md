#Intel Pin Tools basic usage  

## building environment  
下載 Intel Pin Tools [pin](https://software.intel.com/en-us/articles/pintool-downloads)   
解壓縮就可以使用 不用另外安裝  
建議把 ./($pin\_dir)/pin link 到執行路徑底下  

## run sample code  
*source/tools* 底下是 pin 的範例程式碼  
自己寫模組也是放在這個資料夾底下    

根據 README 的步驟來操作:  
`cd source/tools/SimpleExamples`  
`make bj-ia32/opcodemix.so` // obj-ia32 底下會有編出來的 shared object  
`pin -t obj-ia32/opcodemix.so -- /bin/ls`  // 用自訂的 so 分析 /bin/ls  
分析結果在 opcodemix.out  

## write our pintool  
把 *source/tools/MyPinTool* 複製一份  
以此作為模板稍作修改  

*MyPinTool.cpp*: 主要的程式碼 撰寫自己要對 binary 做的分析行為  
*makefile*: 理論上不需要更改到 makefile  
*makefile.rule*: 在這邊可以覆寫編譯時的設定 客製化自己的需求  

這邊簡單介紹一下 sample code 用到的 function  

`Knob`: 這個類別指的是執行 pin 指令時的參數, 可以自訂一些預設值   
`PIN_init()`: 將執行參數傳遞給 pin tool  
`TRACE`: 一個 TRACE 就代表一條 asm 指令  
`TRACE_AddInstrumentFunction`: 定義 trace 的 callback  
`PIN_AddThreadStartFunction`: 定義偵測到有另一個 thread start 的 callback  
`PIN_AddFiniFunction`: 定義程式結束的 callback  
`PIN_StartProgram`: 程式開始  

PIN 的詳細文件可以參考: [pin doc](https://software.intel.com/sites/landingpage/pintool/docs/71313/Pin/html/)  
