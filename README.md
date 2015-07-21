# EST527
A arduino library for EST527.

Based on David Irvine's "arduino-ELM327" library, from https://github.com/irvined1982/arduino-ELM327 .
Just implement minimum function now (speed/rpm) .

此arduino-EST527函式庫, 是基於David Irvine的arduino-ELM327函式庫下去開發, 目前僅有基本的功能被實作出來.

EST527預設運行在 實時數據流廣播(ATRON) 的狀態, 1Hz的頻率廣播目前車速、轉速等等數據.
然而應用在HUD上, 這樣的頻率太慢, 因此建議關閉 實時數據流廣播(ATROFF).
從EST527有兩種方式可以獲得車速: 1.AT指令 2.自定義PID

1.AT指令
透過ES527的AT指令可以簡單地取得車速(AT013), 不用再做OBD數據格式的轉換.
透過AT指令的同時, EST527背後對車輛狀態進行數據統計, 因此AT指令請求間隔最快為100ms.

2.自定義PID
採用自定義PID, EST527會關閉所有統計功能, 自定義PID會直接跟車用網路連結, 達到最快的車速獲取.
若不需要EST527提供的統計功能, 建議採用此模式獲取車速, 但需要自己解析OBD返回的格式.

透過EST527.begin(bool pidMode)可以決定採用 AT指令 或者 自定義PID.