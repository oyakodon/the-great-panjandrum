# CSVフォーマット

|命令の内容|命令|オプション|
|:-:|:-|:-|
|ブロックの生成|CREATEBLOCK|blocktype, x, y, w, h|
|SETPOS|プレイヤー位置の設定|x, y|
|SETGOAL|ゴールの設定|x, y|
|CREATEITEM|アイテムの生成|itemtype, x, y|
|CREATEENEMY|敵の生成|enemytype, x, y|
|※ここまで必須|※以下は時間があれば実装||
|音楽の再生|PLAYSOUND|filepath, volume|
|メッセージの表示|SHOWMSG|message|
|プレイヤーの入力待機|WAITPLAYER||
|メッセージクリア|CLEARMSG||
|画像クリア|CLEARIMG||
|再生停止|STOPSOUND||
|画像の表示|SHOWIMG|filepath, x, y, w, h|