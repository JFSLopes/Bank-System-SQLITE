-- Populate State table
INSERT INTO State (state)
VALUES ('Pending'),
    ('Completed'),
    ('Failed');
-- Populate Type table
INSERT INTO Type (type)
VALUES ('Normal Transfer'),
    ('Urgent Transfer');
-- Populate MyBank table with three banks
INSERT INTO MyBank (name)
VALUES ('National Bank'),
    ('City Bank');