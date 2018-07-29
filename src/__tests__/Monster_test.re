open Jest;

describe("Monster", () => {
  open Expect;
  open! Expect.Operators;

  let monster =
    Monster.create([
      Monster.Text("name", "Leaves Buscemi"),
      Monster.LongText(
        "description",
        "This Buscemi has lovely foliage in the Spring",
      ),
    ]);

  test("can retrieve an existing field from a Monster", () => {
    let field = Monster.getField("name", monster);
    let results =
      switch (field) {
      | Some(Monster.Text(fieldname, fieldvalue)) => (fieldname, fieldvalue)
      | _ => ("", "")
      };
    expect(results) |> toEqual(("name", "Leaves Buscemi"));
  });

  test("returns 'None' if the field does not exist", () => {
    let field = Monster.getField("age", monster);
    expect(field) |> toBe(None);
  });

  test("returns a list of fields", () => {
    let fields = Monster.getAllFields(monster);
    expect(List.length(fields)) |> toBe(2);
  });
});