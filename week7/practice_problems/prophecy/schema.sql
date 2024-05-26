CREATE TABLE houses (
    house_id INTEGER,
    house TEXT,
    PRIMARY KEY(house_id)
);

CREATE TABLE heads (
    head_id INTEGER,
    head TEXT,
    PRIMARY KEY(head_id)
);

CREATE TABLE students (
    id INTEGER,
    student_name TEXT,
    house_id INTEGER,
    head_id INTEGER,
    PRIMARY KEY(id),
    FOREIGN KEY(house_id) REFERENCES houses(house_id),
    FOREIGN KEY(head_id) REFERENCES heads(head_id)
);
