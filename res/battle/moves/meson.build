fs = import('fs')

pl_waza_tbl_subdirs = [
    '0000',
]

move_consts = fs.read(moves_txt).splitlines()
foreach move : move_consts
    if move.startswith('MOVE_') and move != 'MOVE_NONE'
        move_name = move.replace('MOVE_', '').to_lower()
        pl_waza_tbl_subdirs += move_name
    endif
endforeach

pl_waza_tbl_data_srcs = []
foreach subdir : pl_waza_tbl_subdirs
    pl_waza_tbl_data_srcs += subdir / 'data.json'
endforeach

pl_waza_tbl_narc = custom_target('pl_waza_tbl.narc',
    output: 'pl_waza_tbl.narc',
    input: pl_waza_tbl_data_srcs,
    env: jsoncnv_env,
    depends: [ py_consts_generators ],
    command: [
        movedata_py,
        '--narc', nitroarc_exe,
        '--source-dir', '@CURRENT_SOURCE_DIR@',
        '--private-dir', '@PRIVATE_DIR@',
        '--output-dir', '@OUTDIR@',
    ]
)

nitrofs_files += pl_waza_tbl_narc
