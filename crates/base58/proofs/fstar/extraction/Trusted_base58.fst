module Trusted_base58
#set-options "--fuel 0 --ifuel 1 --z3rlimit 15"
open FStar.Mul
open Core_models

let decode (s: string) : Prims.unit =
  let s:string = Core_models.Str.impl_str__trim_start s in
  ()
