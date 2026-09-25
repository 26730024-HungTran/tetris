# Giải thích từng hàm trong `main.cpp`

## Dữ liệu chung
```
board[H][W]  = bảng game 20 dòng x 15 cột ('#' = tường, ' ' = trống, chữ cái = khối)
blocks[b]    = hình khối hiện tại (lưới 4x4)
x, y         = vị trí góc trên-trái của lưới 4x4 trên board
b            = chỉ số khối đang rơi (9..15 = I, O, T, S, Z, J, L)
```

---

## 1) `initBoard()` – tạo bảng
Viền = `#`, bên trong = trống.
```
 # # # # # # #
 # . . . . . #
 # . . . . . #
 # . . . . . #
 # # # # # # #
```

---

## 2) `canMove(dx, dy)` – có di chuyển được không?
Thử dời khối đi (dx, dy), kiểm tra: có ra ngoài tường/đáy không, có đè lên ô đã có không. Trả về true/false.
```
 canMove(0,1)  "xuống 1 hàng được không?"

 # . . T . . #        # . . . . . #
 # . T T T . #   ->   # . . T . . #
 # . . . . . #        # . T T T . #   <- trống: OK (true)
 # . . . . . #        # . . . . . #
 # # # # # # #

 # . . . . . #
 # . . T . . #
 # . T T T . #
 # # # # # # #   <- đáy chặn: false
```

---

## 3) `rotate()` – xoay khối
Xoay lưới 4x4 90° vào bản nháp. Nếu bản nháp vừa (không ra ngoài, không đè) thì mới thay khối thật. Nếu không thì giữ nguyên.
```
 trước          sau khi xoay
 . . . .        . . . .
 . T . .        . T . .
 T T T .   ->   . T T .
 . . . .        . T . .
```

---

## 4) `block2Board()` – ghi khối lên board
Chép từng ô của khối vào `board[y+i][x+j]`. Để `draw()` vẽ được, vì `draw()` chỉ in `board`.
```
 board trước        board sau block2Board
 # . . . . . #      # . . . . . #
 # . . . . . #      # . . T . . #
 # . . . . . #      # . T T T . #
 # # # # # # #      # # # # # # #
```

---

## 5) `boardDelBlock()` – xoá khối khỏi board
Ngược lại của `block2Board`: ô của khối = trống. Để khi kiểm tra `canMove`/`rotate`, khối **không tự va chạm với chính nó**.
```
 # . . . . . #      # . . . . . #
 # . . T . . #      # . . . . . #
 # . T T T . #  ->  # . . . . . #
 # # # # # # #      # # # # # # #
```

Bảng trắng:
```
 boardDelBlock = lau khối
 y++ / x++     = quyết định chỗ mới
 block2Board   = vẽ lại khối ở chỗ mới
```

---

## 6) `removeLine()` – xoá hàng đầy
Quét từ dưới lên. Hàng đầy thì xoá, các hàng phía trên dồn xuống, hàng trên cùng để trống. Trả về số hàng đã xoá.
```
 trước                  sau
 # . . . . . #          # . . . . . #
 # . T . . . #          # . . . . . #
 # T T T S S #  <- đầy  # . T . . . #
 # # # # # # #          # # # # # # #
```

---

## 7) `draw()` – vẽ màn hình
- Đưa con trỏ về (0,0) rồi in đè (không dùng `cls` nữa nên hết nhấp nháy).
- `#` = `##` trắng, khối = `██` (màu theo loại), trống = 2 dấu cách.
```
 board:  T           màn hình:  ██
        T T T                 ██████
```

---

## 8) `main()` – vòng lặp game
```
 Bắt đầu: UTF-8, ẩn con trỏ, cls 1 lần, random khối, initBoard

 Mỗi tick (333ms):
 ┌────────────────────────────────────────────┐
 │ 1) boardDelBlock  -> lau khối khỏi board   │
 │ 2) đọc phím:                               │
 │      a = trái   d = phải   x = xuống       │
 │      w = xoay   q = thoát                  │
 │ 3) trọng lực:                              │
 │      canMove(0,1) ?                        │
 │        có   -> y++ (rơi 1 hàng)            │
 │        không-> block2Board (khoá khối)     │
 │                removeLine (xoá hàng,       │
 │                  tăng tốc nếu có)          │
 │                khối mới: x=5, y=0,         │
 │                b = 9 + rand() % 7          │
 │ 4) block2Board    -> ghi khối lại          │
 │ 5) draw           -> in ra màn hình        │
 │ 6) sleep(speed)   -> chờ                   │
 └────────────────────────────────────────────┘
```

**Tốc độ:** mỗi lần xoá hàng, `speed` giảm 17ms (thấp nhất 67ms).
