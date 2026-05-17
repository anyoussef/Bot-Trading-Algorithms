{
  description = "Bot Paper Traders with Alpaca API C++/React";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs { inherit system; };
      in
      {
        devShells.default = pkgs.mkShell {
          packages = with pkgs; [
            # C++
            nlohmann_json
            curl
            clang
            cmake

            # direnv integration
            direnv

            # React (for later)
            nodejs
          ];

          shellHook = ''
            exec zsh
          '';
        };
      });
}

