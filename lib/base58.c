#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

/*@ logic 𝔹 is_space(char c) =
  @   c ≡ ' ' ∨ c ≡ '\f' ∨ c ≡ '\n' ∨ c ≡ '\r' ∨ c ≡ '\t' ∨ c ≡ '\v';
  @*/

/*@ logic char *skip_spaces(char *s) =
  @   is_space(*s) ? skip_spaces(s + 1) : s;
  @*/

/*@ predicate is_base58_index(ℤ i) = 0 ≤ i < 58;
  @*/

/*@ predicate is_base58_char(ℤ c) =
  @   49 ≤ c ≤ 57
  @ ∨ 65 ≤ c ≤ 72
  @ ∨ 74 ≤ c ≤ 78
  @ ∨ 80 ≤ c ≤ 90
  @ ∨ 97 ≤ c ≤ 107
  @ ∨ 109 ≤ c ≤ 122;
  @*/

/*@ axiomatic IndexToBase58 {
  @   logic char index_to_base58(ℤ i);
  @
  @   axiom index_to_base58_0_8:
  @     ∀ ℤ i; 0 ≤ i ≤ 8 ⇔ index_to_base58(i) ≡ i + 49;
  @   axiom index_to_base58_9_16:
  @     ∀ ℤ i; 9 ≤ i ≤ 16 ⇔ index_to_base58(i) ≡ i - 9 + 65;
  @   axiom index_to_base58_17_21:
  @     ∀ ℤ i; 17 ≤ i ≤ 21 ⇔ index_to_base58(i) ≡ i - 17 + 74;
  @   axiom index_to_base58_22_32:
  @     ∀ ℤ i; 22 ≤ i ≤ 32 ⇔ index_to_base58(i) ≡ i - 22 + 80;
  @   axiom index_to_base58_33_43:
  @     ∀ ℤ i; 33 ≤ i ≤ 43 ⇔ index_to_base58(i) ≡ i - 33 + 97;
  @   axiom index_to_base58_44_57:
  @     ∀ ℤ i; 44 ≤ i ≤ 57 ⇔ index_to_base58(i) ≡ i - 44 + 109;
  @ }
  @*/

/*@ axiomatic Base58ToIndex {
  @   logic ℤ base58_to_index(char i);
  @
  @   axiom base58_to_index_49_57:
  @     ∀ char c; 49 ≤ c ≤ 57 ⇔ base58_to_index(c) ≡ c - 49;
  @   axiom base58_to_index_65_72:
  @     ∀ char c; 65 ≤ c ≤ 72 ⇔ base58_to_index(c) ≡ (c + 9) - 65;
  @   axiom base58_to_index_74_78:
  @     ∀ char c; 74 ≤ c ≤ 78 ⇔ base58_to_index(c) ≡ (c + 17) - 74;
  @   axiom base58_to_index_80_90:
  @     ∀ char c; 80 ≤ c ≤ 90 ⇔ base58_to_index(c) ≡ (c + 22) - 80;
  @   axiom base58_to_index_97_107:
  @     ∀ char c; 97 ≤ c ≤ 107 ⇔ base58_to_index(c) ≡ (c + 33) - 97;
  @   axiom base58_to_index_109_122:
  @     ∀ char c; 109 ≤ c ≤ 122 ⇔ base58_to_index(c) ≡ (c + 44) - 109;
  @ }
  @*/

/*@ lemma is_space_not_is_base58_char:
  @   ∀ char c; is_space(c) ⇒ ¬is_base58_char(c);
  @*/

/*@ lemma is_base58_char_not_is_space:
  @   ∀ char c; is_base58_char(c) ⇒ ¬is_space(c);
  @*/

/*@ lemma not_base58_char_nul: ¬is_base58_char(0);
  @*/

/*@ lemma not_base58_char_0:
  @   ∀ char c; c == 48 ⇒ ¬is_base58_char(c); // '0'
  @*/

/*@ lemma not_base58_char_O:
  @   ∀ char c; c == 79 ⇒ ¬is_base58_char(c); // 'O'
  @*/

/*@ lemma not_base58_char_I:
  @   ∀ char c; c == 73 ⇒ ¬is_base58_char(c); // 'I'
  @*/

/*@ lemma not_base58_char_l:
  @   ∀ char c; c == 108 ⇒ ¬is_base58_char(c); // 'l'
  @*/

/*@ lemma base58_to_index_range:
  @   ∀ char c; is_base58_char(c) ⇒ is_base58_index(base58_to_index(c));
  @*/

/*@ lemma index_to_base58_range:
  @   ∀ ℤ i; is_base58_index(i) ⇒ is_base58_char(index_to_base58(i));
  @*/

/*@ lemma base58_to_index_inverse:
  @   ∀ char c; is_base58_char(c) ⇒ index_to_base58(base58_to_index(c)) ≡ c;
  @*/

/*@ lemma index_to_base58_inverse:
  @   ∀ ℤ i; is_base58_index(i) ⇒ base58_to_index(index_to_base58(i)) ≡ i;
  @*/

/*@ assigns \result \from indirect:i;
  @ behavior valid_index:
  @   requires is_base58_index(i);
  @   ensures \result ≡ index_to_base58(i);
  @ behavior invalid_index:
  @   requires ¬is_base58_index(i);
  @   ensures \result ≡ 0;
  @ complete behaviors;
  @ disjoint behaviors;
  @*/
static inline char
base58_index_to_char (int i)
{
  if (0 <= i && i <= 8)
    return i + 49;
  else if (9 <= i && i <= 16)
    return i - 9 + 65;
  else if (17 <= i && i <= 21)
    return i - 17 + 74;
  else if (22 <= i && i <= 32)
    return i - 22 + 80;
  else if (33 <= i && i <= 43)
    return i - 33 + 97;
  else if (44 <= i && i <= 57)
    return i - 44 + 109;
  else
    return 0;
}

/*@ assigns \result \from c;
  @ behavior valid_character:
  @   requires is_base58_char(c);
  @   ensures \result ≡ base58_to_index(c);
  @ behavior invalid_character:
  @   requires ¬is_base58_char(c);
  @   ensures \result ≡ -1;
  @ complete behaviors;
  @ disjoint behaviors;
  @*/
static inline int
base58_char_to_index (char c)
{
  if (49 <= c && c <= 57)
    return c - 49;
  else if (65 <= c && c <= 72)
    return c + 9 - 65;
  else if (74 <= c && c <= 78)
    return c + 17 - 74;
  else if (80 <= c && c <= 90)
    return c + 22 - 80;
  else if (97 <= c && c <= 107)
    return c + 33 - 97;
  else if (109 <= c && c <= 122)
    return c + 44 - 109;
  else
    return -1;
}

/*@ assigns \result \from c;
  @ ensures \result ≡ is_space(c);
  @*/
static inline bool
base58_is_space (char c)
{
  return c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == '\v';
}

/*@ requires valid_read_string(s);
  @ assigns \result \from indirect:s[0..strlen(s)];
  @ ensures ∀ ℤ i; 0 ≤ i < \result ⇒ s[i] ≡ '1';
  @*/
static inline size_t
base58_eat_leading_ones (const char *s)
{
  size_t i = 0;
  /*@ loop invariant bounds: 0 ≤ i ≤ strlen{Pre}(s);
    @ loop invariant valid: valid_read_string(s + i);
    @ loop invariant ones: ∀ ℤ j; 0 ≤ j < i ⇒ s[j] ≡ '1';
    @ loop invariant continue: s[i] ≡ '1' ⇒ i < strlen{Pre}(s);
    @ loop assigns i;
    @ loop variant strlen{Pre}(s) - i;
    @*/
  while (s[i] != '\0' && s[i] == '1')
    i++;
  return i;
}

///*@ requires valid_read_string(s);
//  @ assigns \result \from s;
//  @ ensures \result == skip_spaces(s);
//  @*/
//static inline const char *
//base58_skip_spaces (const char *s)
//{
//  /*@ loop invariant valid_read_string(s);
//    @ loop assigns s;
//    @*/
//  while (*s && base58_is_space (*s))
//      s++;
//  return s;
//}
//
///*@ requires valid_read_string(s);
//  @ ensures valid_read_string(\result);
//  @*/
//static inline const char *
//base58_decode_prefix (const char *s, size_t *n)
//{
//  return s;
//}
//
///*@ requires valid_read_string(s);
//  @*/
//bool
//base58_decode (const char *s)
//{
//  s = base58_skip_spaces (s);
//
//  return false;
//}
