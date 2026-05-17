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
            nlohmann_json
            curl
            clang
            clang-tools
            cmake
            direnv
            nodejs
          ];

          shellHook = ''
              export CC=clang
              export CXX=clang++
              if [ -f .env ]; then
                export $(cat .env | xargs)
              fi

              cat > .clangd << EOF
            CompileFlags:
              CompilationDatabase: build/
              Add:
                - -isysroot/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk
                - -I${pkgs.nlohmann_json}/include
            EOF

              exec zsh
          '';
        };
      });
}


