type field = {
  id: int,
  order: int,
  name: string,
  value: string,
};

type monster = {
  order: int,
  fields: list(field),
};

type record('a) = {.. id: int} as 'a;

type monsterRecord =
  record({
    .
    id: int,
    monster: monster,
  });
/* type monsterRecord('a) = {.. id: int} as 'a;s */

let store = ref([]: list(monsterRecord));

let getAllMonsters = () => store^;

/**
 * Helper functions to encode JSON
 */
let encodeField = (field: field) =>
  Json.Encode.(
    object_([
      ("id", int(field.id)),
      ("order", int(field.order)),
      ("name", string(field.name)),
      ("value", string(field.value)),
    ])
  );

let encodeMonster = (monster: monster) =>
  Json.Encode.(
    object_([
      ("order", int(monster.order)),
      ("fields", monster.fields |> list(encodeField)),
    ])
  );

let encodeMonsterRecord = (monsterRecord: monsterRecord) =>
  Json.Encode.(
    object_([
      ("id", int(monsterRecord#id)),
      ("monster", monsterRecord#monster |> encodeMonster),
    ])
  );

let encodeStore = (store: list(monsterRecord)) =>
  Json.Encode.(store |> list(encodeMonsterRecord));

let cacheStore = (store: list(monsterRecord)) => {
  let jsonString = store |> encodeStore |> Json.stringify;
  Dom.Storage.(localStorage |> setItem("store", jsonString));
};

/**
 * Helper function to decode JSON
 */

/**
 * A helper funcction to get the next highest ID
 */
let getNextId = () => {
  let id = ref(0);
  if (List.length(store^) > 0) {
    let record = List.hd(store^);
    id := record#id + 1;
  };
  id^;
};

/* let saveStateToStorage = (store: ref(list(monsterRecord))) => {
     let json = Json.Encode.list(store^);
   }; */

/**
 * A helper function to create a monster object
 */
let createMonsterRecord = (~id: int, ~monster: monster) => {
  let monsterRecord: monsterRecord = {pub id = id; pub monster = monster};
  monsterRecord;
};

let addMonster = (monster: monster) => {
  let monsterRecord = createMonsterRecord(~id=getNextId(), ~monster);
  store := [monsterRecord, ...store^];
  cacheStore(store^);
  /* let _save = saveStateToStorage(store); */
  monsterRecord;
};

let getMonster = (~id: int) => {
  let monsterRecord =
    List.find(monsterRecord => monsterRecord#id == id, store^);
  monsterRecord;
};

let getMonsterField = (~id: int, ~fieldName: string) => {
  let monster = getMonster(~id)#monster;
  let field = List.find(field => field.name == fieldName, monster.fields);
  field;
};

let updateMonster = (~id: int, newMonster: monster) => {
  let newMonsterRecord = createMonsterRecord(~id, ~monster=newMonster);
  store :=
    List.map(
      monsterRecord =>
        monsterRecord#id == id ? newMonsterRecord : monsterRecord,
      store^,
    );
  getMonster(~id=newMonsterRecord#id);
};

let removeMonster = (~id: int) =>
  store := List.filter(monsterRecord => id != monsterRecord#id, store^);

store^ |> encodeStore |> Json.stringify;