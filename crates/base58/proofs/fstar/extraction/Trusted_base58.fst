module Trusted_base58
#set-options "--fuel 0 --ifuel 1 --z3rlimit 15"
open FStar.Mul
open Core_models

let trim_start (s: string) : string =
  let i:usize = mk_usize 0 in
  let i:usize =
    Rust_primitives.Hax.while_loop (fun i ->
          let i:usize = i in
          true)
      (fun i ->
          let i:usize = i in
          i <. (Core_models.Str.impl_str__len s <: usize) <: bool)
      (fun i ->
          let i:usize = i in
          Rust_primitives.Hax.Int.from_machine (mk_u32 0) <: Hax_lib.Int.t_Int)
      i
      (fun i ->
          let i:usize = i in
          let i:usize = i +! mk_usize 1 in
          i)
  in
  s

let decode (s: string) : Prims.unit =
  let _:string = trim_start s in
  ()

let is_whitespace (c: u8)
    : Prims.Pure bool
      Prims.l_True
      (ensures
        fun result ->
          let result:bool = result in
          b2t result ==>
          b2t
          ((c =. mk_u8 32 <: bool) || (c =. mk_u8 10 <: bool) || (c =. mk_u8 13 <: bool) ||
            (c =. mk_u8 9 <: bool))) =
  c =. mk_u8 32 || c =. mk_u8 10 || c =. mk_u8 13 || c =. mk_u8 9
