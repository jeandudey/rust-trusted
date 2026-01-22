{
  description = "rust-trusted";

  inputs = {
    aeneas.url = "github:AeneasVerif/aeneas";
    flake-utils.url = "github:numtide/flake-utils";
    fstar.url = "github:FStarLang/FStar";
    hax.url = "github:cryspen/hax";
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = {
    self,
    aeneas,
    flake-utils,
    fstar,
    hax,
    nixpkgs
  }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs { inherit system; };
        aeneasPkgs = aeneas.packages.${system};
        fstarPkgs = fstar.packages.${system};
        haxPkgs = hax.packages.${system};
      in
      {
        devShells.default = pkgs.mkShell {
          packages = [
            aeneasPkgs.aeneas
            pkgs.git
            pkgs.jq
            pkgs.rocq-core
            pkgs.rocqPackages.bignums
            pkgs.rustup
            pkgs.taplo
            pkgs.why3
            pkgs.z3
            fstarPkgs.fstar
            haxPkgs.hax
          ];
        };
      }
    );
}
