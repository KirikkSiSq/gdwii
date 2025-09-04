// values taken from bigFont-hd.fnt
struct glyph {
    int id, x, y, width, height, xoffset, yoffset, xadvance;
};

struct charset {
    struct glyph *chars;
    int char_num;
};

extern struct glyph big_font_chars[96];
extern struct charset big_font;
