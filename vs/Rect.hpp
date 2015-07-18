class Rect {
public:
    int y = 0, x = 0,width=0,height=0;

    bool isContain(int cx,int cy) {
        return (cx >= x && cx <= x + width && cy >= y && cy <= y + height);
    }
};