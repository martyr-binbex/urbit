{ lib, stdenvNoCC, fetchGitHubLFS, bootFakeShip, solid, urbit, arvo, herb
, withRopsten ? false }:

let

  lfs = fetchGitHubLFS { src = ../../../bin/tin.pill; };

in {
  build = import ./builder.nix {
    inherit stdenvNoCC urbit herb;

    name = "tin" + lib.optionalString withRopsten "-ropsten";
    builder = ./tin.sh;
    arvo = if withRopsten then arvo.ropsten else arvo;
    pier = bootFakeShip {
      inherit urbit herb;
      pill = "/Users/philip/source/urbit/bin/solid.pill";
      #pill = solid.lfs;
      ship = "zod";
    };
  };
} // lib.optionalAttrs (!withRopsten) { inherit lfs; }
