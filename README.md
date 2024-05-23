# Gold miner 
# Mô tả
- Ngôn ngữ lập trình: C++ và SDL2.
- Dự án tái tạo lại game **đào vàng** tuổi thơ.
- Lấy bối cảnh phim hoạt hình **Leprechaun**, chúng ta được hóa thân vào nhân vật yêu tinh, nhưng thay vì đi cướp vàng thì nhân vật quyết định làm lụng, bước vào hành trình đi tìm kho báu, làm ăn chân chính.

# Các thành phần
- **Home Menu**: background, Quit button, Mute/UnMute Button, SinglePlayer (ấn vào để chơi ở chế độ đơn), Multiplayer (update sau)
  ![HomeMenu](https://github.com/sonbipayacctu10namtrc/SDL2_Project/blob/main/ExPhoto/HomeMenuGame.png)
- **Game Main**: có 3 màn chơi
  - ***map***: Đọc từ file txt, lấy các object và time cho mỗi màn.
  - ***object***: rock, gold, diamond với 3 kích cỡ cơ bản: nhỏ, vừa và lớn.
  - ***time***: lấy từ file txt, càng về map sau, thời gian càng ngắn.
  - ***Button***: pause / Unpause Button, Music Button, Quit Button, Home Menu Button.
  ![GameMain](https://github.com/sonbipayacctu10namtrc/SDL2_Project/blob/main/ExPhoto/GameMain.png)
- **Game Over**: hiện màn hình kết thúc trò chơi, hiện số điểm
  ![GameOver](https://github.com/sonbipayacctu10namtrc/SDL2_Project/blob/main/ExPhoto/GameOverGame.png)

  # Kiến thức sử dụng
  - Algorithm: pair(map), vector, string.
  - Đọc file.
  - 1 chút OOP.
  - SDL2

# Nguồn tham khảo
- Image:
- Ý tưởng code: nhiều nguồn
- Học code:
  https://lazyfoo.net/tutorials/SDL/index.php
  SDL2: https://www.youtube.com/watch?v=QQzAHcojEKg&list=PLhfAbcv9cehhkG7ZQK0nfIGJC_C-wSLrx
        https://www.youtube.com/watch?v=KsG6dJlLBDw&list=PL2RPjWnJduNmXHRYwdtublIPdlqocBoLS
        https://www.youtube.com/@PolyMars
  C++: w3school, hackerrank, geeksforgeeks, 28tech

> [!IMPORTANT]
> Code vẫn còn một số lỗi đến giờ vẫn chưa fix được, mong mọi người thông cảm.

> [!NOTE]
> Nếu bị lỗi thư viện thì cài lại đường dẫn thư viện rồi sau đó mới chạy.  
