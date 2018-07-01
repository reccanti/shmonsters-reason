type id = int;
type content('a);
type record('a) = (id, content('a));

type store('a) = {
  backend: option(Backend.t),
  records: list(record('a)),
};

/**
 * This will create a store with a backend if one was provided
 */
let make = (~backend: option(Backend.t)=None, ()) => {backend, records: []};

let getAllAsList = store => store.records;

let get = (searchId: id, store: store('a)) => {
  let (_, content) =
    store.records |> List.find(((id, _)) => id == searchId);
  content;
};

/**
 * Create a new record from the given information and insert
 * it into the store
 */
let set = (searchId: id, content: content('a), store: store('a)) => {
  let newRecord = (searchId, content);
  let newRecords =
    store.records
    |> List.map(((id, content)) =>
         id == searchId ? newRecord : (id, content)
       );
  /* if (store.backend) {
       Backend.save("hello", store.backend);
     }; */
  {backend: store.backend, records: newRecords};
};