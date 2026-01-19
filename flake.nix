{
  description = "rust-trusted";

  inputs = {
    flake-utils.url = "github:numtide/flake-utils";
    fstar.url = "github:FStarLang/FStar";
    hax.url = "github:cryspen/hax";
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = { self, flake-utils, fstar, hax, nixpkgs }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs { inherit system; };
        fstarPkgs = fstar.packages.${system};
        haxPkgs = hax.packages.${system};
      in
      {
        devShells.default = pkgs.mkShell {
          packages = [
            pkgs.git
            pkgs.jq
            pkgs.rustup
            pkgs.taplo
            fstarPkgs.fstar
            haxPkgs.hax
          ];
        };
      }
    );
}
