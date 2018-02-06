# CSVフォーマット

|命令の内容|命令|オプション|
|:-:|:-|:-|
|ブロックの生成|CREATEBLOCK|blocktype, x, y, w, h, [V/H], [range]|
|プレイヤー位置の設定|SETPOS|x, y|
|ゴールの設定|SETGOAL|x, y, nextstage|
|アイテムの生成|CREATEITEM|itemtype, x, y|
|敵の生成|CREATEENEMY|enemytype, x, y, [range]|
|ステージ名を設定|SETNAME|name|

---

- blocktype
  - BLOCK
  - MOVINGBLOCK
- itemtype
  - TEA
  - MARMITE
- enemytype
  - BUNCHIN
  - YOTIYOTI
  - DANMAKU

## メモ
- CREATEBLOCK
  - blocktype == MOVINGBLOCKの時は、V/H(縦移動/横移動を指定し、さらに横移動の場合はrange(ブロックの移動範囲, 座標)を指定すること。
- CREATEENEMY
  - enemytype == YOTIYOTI の時は、range(どの範囲を移動するか, 座標)を指定すること