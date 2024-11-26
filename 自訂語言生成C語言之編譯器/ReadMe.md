## 專案說明
在本次專案中，我們要透過Yacc與Lex等工具對QV這個自訂義的程式語言進行編譯，生成對應的Ｃcode，
而在解析自訂義語言的過程中，需要選擇適當的資料結構以保存解析符號的資料，並在解析到對應的符號
後進行對應的操作。
## 檔案說明  
main.c:　輸入與輸出的主檔案  
lex.l, yacc.y:　Yacc與Lex的解析規則


## 使用方法(要安裝Boost Libraries才可以正常使用)
    1. 進入此專案
    2. 輸入 cmake .
    3. 輸入 make
       編譯專案並產生執行檔 main
    4. 輸入 ./main [sample.blif]
        sample.blif: 要簡化的.blif檔
    5. 產生out.blif檔，並顯示化簡後的邏輯數量


## 測試結果
以下為執行./main sample.blif後的結果，簡化後的邏輯會透過Ex(x為任意數字)變數進行擴充，以組成等效的布林代數
![image](https://github.com/user-attachments/assets/a52d495d-79bb-4be0-b2ba-f33dcd8efcc3)

