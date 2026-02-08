# Pokémon Tempered Platinum Engine Base

This is the rough engine for Pokémon Tempered Platinum, based on the WIP decompilation of Pokémon Platinum. All credit for the base decompilation goes to the pret community, see [pret.github.io](https://pret.github.io/). In addition to the pret Discord, also see the [VoidMatrix Discord (#decomp)](https://discord.gg/prUAgd5). If you are interested in contributing to the pret decompilation, please read [`CONTRIBUTING.md`](/CONTRIBUTING.md) and join the Discord. Do not make pull requests to this fork.

More accurately, this repository is an update to Pokémon Platinum to update all of the mechanics from generation IX and beyond in an earlier game. Note: this does not add mechanics, moves, etc that _only exist in later games_ - it is purely an overhaul of existing mechanics to ensure that the generation IV games perform similarly to what would be expected in generation IX.

However, this is _slightly_ bastardised in some ways. I have only made all of the changes necessary for building Pokémon Tempered Platinum. In the event that there are updates to moves or abilities that have been quietly removed from Pokémon Tempered Platinum, those changes will not be found in this repository. I have documented a full list of changes in this Markdown file, and the [move/abilities branch](https://github.com/matt-newhall/plat-hack-decomp/pull/14) is well documented if you wish to read over specific changes.

In addition, this repository also contains a number of additional features, such as new weather conditions that were required for Pokémon Tempered Platinum. Again, if you wish to maintain this project (or update it - I'm sure there are some much better ways to update some of these mechanics, but I'm not a C programmer!), I would advise forking the repository and removing these commits. Feel free to reach out to me on Discord (@stitchmatt) and I'll be happy to answer any questions.

## Setup

For instructions on how to set up the repository, please read [`INSTALL.md`](INSTALL.md).

This repository builds the following ROMs:

* [**pokeplatinum.us.nds**](https://datomatic.no-intro.org/index.php?page=show_record&s=28&n=3541) `sha1: ce81046eda7d232513069519cb2085349896dec7` *

*: the original decompilation builds to this SHA hash - as we are making edits to the ROM, this hash will be different. However, the ROM size is unaltered currently, allowing you to use this ROM in all existing tools such as DSPRE, etc (hopefully)

For contacts and other pret projects, see [pret.github.io](https://pret.github.io/). In addition to the pret Discord, also see the [VoidMatrix Discord (#decomp)](https://discord.gg/prUAgd5).
