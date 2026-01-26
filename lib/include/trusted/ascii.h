#ifndef __TRUSTED_ASCII_H__
#define __TRUSTED_ASCII_H__

#include <ctype.h>
#include <string.h>

/*@ logic 𝔹 is_ascii_whitespace(ℤ c) =
  @   c ≡ ' ' ∨ c ≡ '\f' ∨ c ≡ '\n' ∨ c ≡ '\r' ∨ c ≡ '\t' ∨ c ≡ '\v';
  @*/

/*@ lemma is_ascii_whitespace_char: is_ascii_whitespace(' ');
  @*/

/*@ lemma is_ascii_whitespace_range:
  @   ∀ ℤ c; 9 ≤ c ≤ 13 ⇒ is_ascii_whitespace(c);
  @*/

/*@ lemma not_is_ascii_whitespace_eof: ¬is_ascii_whitespace(EOF);
  @*/

/*@ lemma not_is_ascii_whitespace_range_0_8:
  @   ∀ ℤ c; 0 ≤ c ≤ 8 ⇒ ¬is_ascii_whitespace(c);
  @*/

/*@ lemma not_is_ascii_whitespace_range_14_whitespace:
  @   ∀ ℤ c; 14 ≤ c < ' ' ⇒ ¬is_ascii_whitespace(c);
  @*/

/*@ lemma not_is_ascii_whitespace_range_whitespace_127:
  @   ∀ ℤ c; ' ' < c ≤ 127 ⇒ ¬is_ascii_whitespace(c);
  @*/

/*@ requires valid_string_s: valid_read_string(s);
  @ assigns \result \from s, indirect:s[0 .. strlen(s)];
  @ behavior string_is_empty:
  @   requires length_is_zero: strlen(s) ≡ 0;
  @   ensures result_is_equal: \result ≡ s;
  @ behavior string_is_positive:
  @   requires length_is_positive: 0 < strlen(s);
  @   ensures equal_base_addr: \base_addr(\result) ≡ \base_addr(s);
  @   ensures trimmed: strlen(\result) != strlen(s) ⇒ ∀ ℤ i; 0 ≤ i < strlen(s) - strlen(\result) ⇒ is_ascii_whitespace((unsigned char)s[i]) ≡ \true;
  @ disjoint behaviors;
  @ complete behaviors;
  @*/
const char *
trusted_ascii_str_trim_start (const char *s);

#endif
