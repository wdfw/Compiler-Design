## 專案說明
在本次專案中，我們要透過Yacc與Lex等工具對QV這個自訂義的程式語言進行編譯，生成對應的Ｃcode，
而在解析自訂義語言的過程中，需要選擇適當的資料結構以保存解析符號的資料，並在解析到特定符號後進行對應的操作。
## 檔案說明  
main.c: 輸入與輸出的主檔案  
main.h: 資料結構與各種對應操作的實現 (在.h實現是因為lex.l, yacc.y的生成順序會與main.c或其他.c檔衝突)  
lex.l, yacc.y: 解析文本與生成的規則，Yacc與Lex等工具會基於此規則生成對應的C code
sample.qv: 使用QV語言的測試檔案  
gec.c: 將QV編譯後的C語言  
[Compiler2024]B10902227-codegenerate.pdf: 本專案實現的功能
## 使用方法(要安裝Yacc與Lex才可以正常使用)
    1. 進入此專案
    2. 輸入 make
       編譯專案並產生執行檔 codeGenerator
    4. 輸入 ./codeGenerator [sample.qv] [out.c]
        sample.qv: 要編譯的.qv檔
        out.c: 輸出的.c檔
    5. 產生gen.c

## 測試結果
sample.qv會宣告一個3X3的矩陣並將其顯示，並將其轉置後再顯示一次  
以下為執行./codeGenerator sample.qv gen.c後的結果
### sample.qv
![image](https://github.com/user-attachments/assets/7ad4a9e0-cdb7-445f-9a14-d667c3c1383a)
### gen.c
![image](https://github.com/user-attachments/assets/57c1dd4d-5475-4041-8398-ea654b7b2da6)
### gen.c的執行檔
![image](https://github.com/user-attachments/assets/3fa04577-0ac9-4972-9465-03e80c614866)
