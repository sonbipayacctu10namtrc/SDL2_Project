# Gold miner 
# Mô tả
- Ngôn ngữ lập trình: C++ và SDL2.
- Dự án tái tạo lại game **đào vàng** tuổi thơ.
- Lấy bối cảnh phim hoạt hình **Leprechaun**, chúng ta được hóa thân vào nhân vật yêu tinh, nhưng thay vì đi cướp vàng thì nhân vật quyết định làm lụng, bước vào hành trình đi tìm kho báu, làm ăn chân chính.

# Các thành phần
- **Home Menu**: background, Quit button, Mute/UnMute Button, SinglePlayer (ấn vào để chơi ở chế độ đơn), Multiplayer (update sau)
- **Game Main**: có 3 màn chơi
  - ***map***: Đọc từ file txt, lấy các object và time cho mỗi màn.
  - ***object***: rock, gold, diamond với 3 kích cỡ cơ bản: nhỏ, vừa và lớn.
  - ***time***: lấy từ file txt, càng về map sau, thời gian càng ngắn.
  - ***Button***: pause / Unpause Button, Music Button, Quit Button, Home Menu Button.

- **Game Over**: hiện màn hình kết thúc trò chơi, hiện số điểm

# Nguồn tham khảo
- Image:
- Ý tưởng code: nhiều nguồn 

> [!IMPORTANT]
> Code vẫn còn một số lỗi đến giờ vẫn chưa fix được, mong mọi người thông cảm.

> [!NOTE]
> Nếu bị lỗi thư viện thì cài lại đường dẫn thư viện rồi sau đó mới chạy.  
