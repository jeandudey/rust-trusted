pub fn decode(s: &str) {
    let _ = trim_start(s);
}

fn trim_start(s: &str) -> &str {
    let mut i = 0;
    while i < s.len() {
        i += 1;
    }
    s
}

//#[hax_lib::ensures(|result| hax_lib::Prop::implies(result.into(), c == b' ' || c == b'\n' || c == b'\r' || c == b'\t') )]
fn is_whitespace(c: u8) -> bool {
    c == b' ' /* || c == '\f' */ || c == b'\n' || c == b'\r' || c == b'\t' /* || c == '\v' */
}
