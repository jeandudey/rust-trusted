pub fn decode(s: &str) {
    let s = eat_whitespace(s);
    let (s, zeros) = eat_leading_ones(s);
}

fn eat_leading_ones(s: &str) -> (&str, usize) {
    let bytes = s.as_bytes();
    let mut i = 0;
    while i < bytes.len() {
        if bytes[i] == b'1' {
            i += 1;
        } else {
            break;
        }
    }
    (&s[i..], i)
}

fn eat_whitespace(s: &str) -> &str {
    let bytes = s.as_bytes();
    let mut i = 0;
    while i < bytes.len() {
        if is_whitespace(bytes[i]) {
            i += 1;
        } else {
            break;
        }
    }
    &s[i..]
}

fn is_whitespace(c: u8) -> bool {
    c == b' ' || c == b'\x0C' || c == b'\n' || c == b'\r' || c == b'\t' || c == b'\x0B'
}
