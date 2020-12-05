# ACM_ICPC
# input file map.txt
- Dòng đầu tiên là kích thước bản đồ (số dòng, số cột)
- n dòng tiếp theo gồm 2m dòng, mỗi cặp số thì phần đầu là điểm của ô đó nếu 1 đội chiếm đc, phần sau nhận một trong 3 giá trị: 0 là ô của đội mình, 1 là của đội bạn, -1 là ô chưa thuộc bất kỳ đội nào.
- Dòng tiếp theo là k, số lượng agent
- 2 * k dòng tiếp theo là vị trí của các agent, k dòng đầu tiên là vị trí các agent của đội mình, k dòng tiếp theo là vị trí các agent của đội bạn.
# Output:
- Trả về 1 vector chưa các move của agent

Mỗi move của agent sẽ là bộ ba giá trị: dx, dy và mv; dx, dy là lượng dịch chuyển trên x, y. mv = 1: nếu ta di chuyển đến ô x + dx, y + dy; mv = 0: xóa tile của đội bạn ở ô x + dx và y + dy.
