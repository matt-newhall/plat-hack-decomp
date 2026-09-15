subdir('common_anims')
subdir('effects')
subdir('moves')
subdir('subscripts')

relative_build_dir = fs.relative_to(meson.current_build_dir(), meson.project_build_root())

# these scripts get loaded into a fixed-size slot in memory with no size check at
# runtime. any too big spills over and corrupts the active mon's battle
# data, so the size limit is enforced here at build time instead.
battle_script_bytes_max = 0
foreach line : fs.read(meson.project_source_root() / 'include' / 'constants' / 'battle.h').split('\n')
    if line.strip().startswith('#define BATTLE_SCRIPT_SIZE_MAX')
        battle_script_bytes_max = line.split('BATTLE_SCRIPT_SIZE_MAX')[1].strip().to_int() * 4
    endif
endforeach

if battle_script_bytes_max == 0
    error('could not read BATTLE_SCRIPT_SIZE_MAX from include/constants/battle.h')
endif

battle_script_size_args = ['--max-size', battle_script_bytes_max.to_string()]

be_seq_target_name = 'be_seq.narc'
waza_seq_target_name = 'waza_seq.narc'

sub_seq_basename = 'sub_seq'
sub_seq_narc_name = sub_seq_basename + '.narc'
sub_seq_naix_name = sub_seq_basename + '.naix'

be_seq_private_dir = relative_build_dir / be_seq_target_name + '.p'
sub_seq_private_dir = relative_build_dir / sub_seq_narc_name + '.p'
waza_seq_private_dir = relative_build_dir / waza_seq_target_name + '.p'

be_seq_narc = custom_target(be_seq_target_name,
    output: be_seq_target_name,
    input: script_bin_gen.process(
        effect_script_files,
        extra_args: ['--out-dir', be_seq_private_dir] + battle_script_size_args
    ),
    command: [
        nitroarc_exe,
        '--create',
        '--file', '@OUTPUT0@',
        '@PRIVATE_DIR@',
    ],
)

sub_seq_narc = custom_target(sub_seq_narc_name,
    output: [
        sub_seq_narc_name,
        sub_seq_naix_name,
    ],
    input: script_bin_gen.process(
        subscript_files,
        extra_args: ['--out-dir', sub_seq_private_dir] + battle_script_size_args
    ),
    command: [
        nitroarc_exe,
        '--create',
        '--index',
        '--files-from', sub_seq_narc_order,
        '--file', '@OUTPUT0@',
        '@PRIVATE_DIR@',
    ],
)

waza_seq_narc = custom_target(waza_seq_target_name,
    output: waza_seq_target_name,
    input: script_bin_gen.process(
        move_script_files,
        extra_args: ['--out-dir', waza_seq_private_dir] + battle_script_size_args
    ),
    command: [
        nitroarc_exe,
        '--create',
        '--file', '@OUTPUT0@',
        '@PRIVATE_DIR@',
    ],
)

nitrofs_files += be_seq_narc
nitrofs_files += sub_seq_narc
nitrofs_files += waza_seq_narc

naix_headers += sub_seq_narc[1]
