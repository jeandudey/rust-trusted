#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

static const char *base58_char_table = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";

static const int8_t base58_index_table[256] = {
  -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
  -1, 0, 1, 2, 3, 4, 5, 6,  7, 8,-1,-1,-1,-1,-1,-1,
  -1, 9,10,11,12,13,14,15, 16,-1,17,18,19,20,21,-1,
  22,23,24,25,26,27,28,29, 30,31,32,-1,-1,-1,-1,-1,
  -1,33,34,35,36,37,38,39, 40,41,42,43,-1,44,45,46,
  47,48,49,50,51,52,53,54, 55,56,57,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
};

/*@ predicate is_space(char c) =
  @   c ≡ ' ' ∨ c ≡ '\f' ∨ c ≡ '\n' ∨ c ≡ '\r' ∨ c ≡ '\t' ∨ c ≡ '\v';
  @*/

/*@ logic char *skip_spaces(char *s) =
  @   (*s ≡ ' ' ∨ *s ≡ '\f' ∨ *s ≡ '\n' ∨ *s ≡ '\r' ∨ *s ≡ '\t' ∨ *s ≡ '\v') ? skip_spaces(s + 1) : s;
  @*/

/*@ predicate is_base58_index(ℤ i) = 0 <= i < 58;
  @*/

/*@ predicate is_base58_char(ℤ c) =
  @   49 ≤ c ≤ 57 ∨ 65 ≤ c ≤ 72  ∨ 74  ≤ c ≤ 78
  @ ∨ 80 ≤ c ≤ 90 ∨ 97 ≤ c ≤ 107 ∨ 109 ≤ c ≤ 122;
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
  @     ∀ ℤ i; 17 ≤ i ≤ 21 ⇔ index_to_base58(i) ≡ i - 22 + 80;
  @   axiom index_to_base58_33_43:
  @     ∀ ℤ i; 33 ≤ i ≤ 43 ⇔ index_to_base58(i) ≡ i - 33 + 97;
  @   axiom index_to_base58_44_57:
  @     ∀ ℤ i; 44 ≤ i ≤ 57 ⇔ index_to_base58(i) ≡ i - 44 + 57;
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

/* lemma index_to_base58_table:
     ∀ ℤ i; is_base58_index(i) ⇒ index_to_base58(i) ≡ base58_char_table[i];
  */

/* lemma base58_to_index_table:
     ∀ char c; is_base58_char(c) ⇒ base58_to_index(c) ≡ base58_index_table[c];
  */

/*@ assigns \result \from c;
  @ ensures is_space(c);
  @*/
static inline bool
base58_is_space (char c)
{
  return c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == '\v';
}

/*@ requires valid_read_string(s);
  @ assigns \result \from s;
  @ ensures \result == skip_spaces(s);
  @*/
static inline const char *
base58_skip_spaces (const char *s)
{
  size_t i = 0;
  /*@ loop invariant 0 ≤ i ≤ strlen(s);
    @ loop assigns i;
    @*/
  while (s[i] && base58_is_space (s[i]))
    {
      i += 1;
    }
  return &s[i];
}

/*@ requires valid_read_string(s);
  @ ensures valid_read_string(\result);
  @*/
static inline const char *
base58_decode_prefix (const char *s, size_t *n)
{
  return s;
}

/*@ requires valid_read_string(s);
  @*/
bool
base58_decode (const char *s)
{
  s = base58_skip_spaces (s);

  return false;
}
