כאן אסביר איך מימשתי את המטלה ואת שיטות ההרצה השונות שיצרתי ב-MakeFile.

המחלקה **node.hpp/tpp** - יוצרת Node בודד שמכיל ערך ומחזיקה וקטור שמכיל את הילדים שלו, יש בה פונקציה להוספת ילד. 

המחלקה **tree.hpp/tpp** - יוצרת עץ מסוג בינארי, או k-ארי לבחירתנו ובעלת הפונקציות להוספת ילד, מחיקת ילד, הוספת שורש, מציאת Node, 
הדפסת העץ למסך בעזרת GUI, איטרטורים שממיינים לפי pre-order, post-order, סריקת bfs, סריקת dfs וערימה בינומית.
בנוסף יש גם Destructor שמוחק את העץ לאחר סיום הפונקציה.

מימוש ה-**pre_order**: נעשה ע״י תור שמכניס כל פעם שורש בן שמאלי בן ימני וככה בעצם לאחר הסריקה נקבל תור שיכיל אותם בסדר הזה.

מימוש ה-**in_order**: נעשה ע״י תור שמכניס כל פעם בן שמאלי שורש בן ימני וככה בעצם לאחר הסריקה נקבל תור שיכיל אותם בסדר הזה.

מימוש ה-**post_order**: נעשה ע״י תור תור שמכניס כל פעם בן שמאלי בן ימני שורש וככה בעצם לאחר הסריקה נקבל תור שיכיל אותם בסדר הזה.

מימוש ֿה-**סריקת bfs**: נעשה ע״י תור שמכניס לפי בדיקה רוחבית על רמות העומק בעץ. וככה בעצם לאחר הסריקה נקבל תור שיכיל את העץ לפי הרמות בסדר.

מימוש ה-**סריקת dfs**: נעשה ע״י תור שמכניס לפי בדיקה לעומק על העץ שכל פעם נרד ברמה וככה נכניס עד שנחזור למעלה, כאשר בן שמאלי קודם לבן ימני.

מימוש ה-**ערימה בינומית**

כמו שאמרתי ע״י make tests נריץ טסטים שבודקים את כל הפונקציות הנ״ל ובודקים שהם מתממשות כראוי. זה בגדול רוב הפונקציות המרכזיות (:
