# CSVフォーマット

|命令の内容|命令|オプション|
|:-:|:-|:-|
|ブロックの生成|CREATEBLOCK|blocktype, x, y, w, h|
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
  - IMMOVABLE
  - TOTTER
  - BARRAGE

## メモ
- CREATEENEMY
  - enemytype == TOTTER の時は、range(どの範囲を移動するか, 座標)を指定すること