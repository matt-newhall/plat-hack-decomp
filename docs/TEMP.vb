BattleSwitchInAI:
  AI_Party (Pokemon[])
  Defender (Pokemon, {HP, Type1, Type2, ...Moves})

  pickedPokemon = 6
  score = 0
  maxScore = 0
  bool disregardCurrentPokemon

  IsFastSlowKill:
    For (AI_Pokemon, count) in AI_Party:
      disregardCurrentPokemon = False

      If AI_Pokemon.HP <= 0:
        Continue

      For AI_Move in Get_Moves(AI_Pokemon):

        // If we have already found that the Pokemon is fast killed, skip
        If disregardCurrentPokemon:
          Continue

        If MaxDamage(AI_Move, Defender) >= Defender.HP
          AI_Move_Priority = GetPriority(AI_Move)

          For Player_Move in Defender.Moves:
            Player_Move_Priority = GetPriority(Player_Move)

            // Fast kill
            If ((AI_Move_Priority > Player_Move_Priority) || ((AI_Move_Priority == Player_Move_Priority) && (AI_Move_Power > Player_Move_Power))):
              Return count

            // Check is not dead, and then slow kill, do we need to check PP ?
            Else:
              For Player_Move in Defender.Moves:
                If MaxDamage(Player_Move, AI_Pokemon) >= AI_Pokemon.HP
                  disregardCurrentPokemon = True
                  Break

              If !disregardCurrentPokemon:
                score = 100
                if score > maxScore:
                  maxScore = 100
                  pickedPokemon = count
