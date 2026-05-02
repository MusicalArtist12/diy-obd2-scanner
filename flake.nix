{

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs = { self, nixpkgs}:
    let
        system = "x86_64-linux";
        pkgs = import nixpkgs {
            inherit system;
            config = { allowUnfree = true; };
        };
    in {
        devShells.${system}.default = pkgs.mkShell {
            buildInputs = with pkgs; [
                arduino-cli
                python313Packages.pyserial
            ];
            shellHook = ''
                arduino-cli core install --config-dir /home/julia/Projects/CAN/data arduino:avr
            '';
        };

    };
}