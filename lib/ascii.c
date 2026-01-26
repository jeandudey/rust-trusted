#include <trusted/ascii.h>

const char *
trusted_ascii_str_trim_start (const char *s)
{
  const size_t n = strlen(s);
  size_t i = 0;
  /*@ loop invariant bounds: 0 ≤ i ≤ n;
    @ loop invariant valid: valid_read_string(s + i);
    @ loop invariant is_whitespace: ∀ ℤ j; 0 ≤ j < i ⇒ is_ascii_whitespace((unsigned char)s[j]) ≡ \true;
    @ loop assigns i;
    @ loop variant n - i;
    @*/
  while (i < n && isspace((unsigned char)s[i]))
    i++;
  return s + i;
}
