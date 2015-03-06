#Intel Pin Tools basic usage  

## Building Environment  
下載 [Intel Pin Tools](https://software.intel.com/en-us/articles/pintool-downloads)   
解壓縮就可以使用 不用另外安裝  
將解壓縮出來的資料夾 加入 $PATH  

## What Is Pin
pin 是 intel 開發的一個 binary analysis framework  
支援 x86/x64 & windows/linux/mac  
pin 提供許多分析 binary 用的 api  
使用者可以用 C/C++ 呼叫 api 來撰寫自己的 pintool  

## Run Sample Code  
*source/tools* 是 pintools 的預設路徑  
底下已經有一些現成 pintools 可以使用  

根據 README 的步驟來操作:  
`cd source/tools/SimpleExamples`  
`make obj-ia32/opcodemix.so` // 編完的 pintool 是一個 share object 存在 obj-ia32 底下  
`pin -t obj-ia32/opcodemix.so -- /bin/ls`  // 用 pintool 分析 /bin/ls  
分析結果在 opcodemix.out  

## Write Our Pintool  
複製 *source/tools/MyPinTool* 稍作修改  

*MyPinTool.cpp*: 主要的程式碼 撰寫自己要對 binary 做的分析行為  
*makefile*: 理論上不需要更改到 makefile  
*makefile.rule*: 覆寫編譯時的設定 客製化自己的需求  

簡單介紹一下 sample code 用到的 function  

`Knob`: 這個類別指的是執行 pin 指令時的參數, 可以自訂一些預設值   
`PIN_init()`: 將執行參數傳遞給 pin tool  
`INS`: INS 類別代表 asm 指令  
`INS_AddInstrumentFunction`: 定義分析 INS 的 callback  
`TRACE`: TRACE 類別是 JIT 時分析定義的一種指令區塊 有一個進入點和數個離開點   
`TRACE_AddInstrumentFunction`: 定義 TRACE 的 callback  
`PIN_AddThreadStartFunction`: 定義偵測到有另一個 thread start 的 callback  
`PIN_AddFiniFunction`: 定義程式結束的 callback  
`PIN_StartProgram`: 程式開始  

PIN 的詳細文件可以參考: [Pin 2.14 User Guide](https://software.intel.com/sites/landingpage/pintool/docs/71313/Pin/html/)  
