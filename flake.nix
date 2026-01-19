{
  description = "rust-trusted";

  inputs = {
    flake-utils.url = "github:numtide/flake-utils";
    hax.url = "github:cryspen/hax";
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = { self, flake-utils, hax, nixpkgs }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs { inherit system; };
        haxPkgs = hax.packages.${system};
      in
      {
        devShells.default = pkgs.mkShell {
          packages = [
            pkgs.git
            pkgs.rustup
            pkgs.taplo
            haxPkgs.hax
          ];
        };
      }
    );
}
