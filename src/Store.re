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

type monsterRecord('a) = {.. id: int} as 'a;

let store =
  ref(
    []:
        list(
          monsterRecord({
            .
            id: int,
            monster: monster,
          }),
        ),
  );

let getAllMonsters = () => store^;

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

/**
 * A helper function to create a monster object
 */
let createMonsterRecord = (~id: int, ~monster: monster) => {
  let monsterRecord: monsterRecord({
    .
    id: int,
    monster: monster
  }) = {
    pub id = id;
    pub monster = monster;
  };
  monsterRecord;
}

let addMonster = (monster: monster) => {
  let monsterRecord = createMonsterRecord(~id=getNextId(), ~monster);
  store := [monsterRecord, ...store^];
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
      monsterRecord => monsterRecord#id == id ? newMonsterRecord : monsterRecord,
      store^,
    );
  getMonster(~id=newMonsterRecord#id);
};

let removeMonster = (~id: int) =>
  store := List.filter(monsterRecord => id != monsterRecord#id, store^);