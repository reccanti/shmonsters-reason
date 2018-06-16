type field = {
  id: int,
  order: int,
  name: string,
  value: string,
};

type monster = {
  id: int,
  order: int,
  fields: list(field),
};

let store = ref([]: list(monster));

let getAllMonsters = () => store^;

let addMonster = monster => {
  store := [monster, ...store^];
  monster;
};

let getMonster = (~id: int) => {
  let monster = List.find(monster => monster.id == id, store^);
  monster;
};

let getMonsterField = (~id: int, ~fieldName: string) => {
  let monster = getMonster(~id);
  let field = List.find(field => field.name == fieldName, monster.fields);
  field;
};

let updateMonster = (~id: int, newMonster: monster) => {
  store :=
    List.map(monster => id == newMonster.id ? newMonster : monster, store^);
  newMonster;
};

let removeMonster = (~id: int) =>
  store := List.filter(monster => id != monster.id, store^);