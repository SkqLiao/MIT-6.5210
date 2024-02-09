import qualified Data.Sequence as Seq
import Data.Foldable (toList)
import Data.Maybe (fromMaybe)
import Data.Time.Clock
import System.IO

data Node = Node {
    val :: Int,
    left :: Maybe Node,
    right :: Maybe Node
}

type Nodes = Seq.Seq Node

execute :: Int -> [Int] -> Nodes -> IO Node
execute n [ver, 1, pos, value] roots = do
    let root = Seq.index roots ver
    -- putStrLn $ "modify " ++ show ver ++ " " ++ show pos ++ " " ++ show value
    return $ modify root 1 n pos value
execute n [ver, 2, pos] roots = do
    let root = Seq.index roots ver
    let result = query root 1 n pos
    print result
    -- putStrLn $ "query " ++ show ver ++ " " ++ show pos ++ " = " ++ show result
    return root

modify :: Node -> Int -> Int -> Int -> Int -> Node
modify node@(Node val lch rch) l r p newVal
    | l == r = node { val = newVal }
    | otherwise =
        let m = (l + r) `div` 2
            updatedLeft = if p <= m then Just (modify (fromMaybe defaultNode lch) l m p newVal) else lch
            updatedRight = if p > m then Just (modify (fromMaybe defaultNode rch) (m + 1) r p newVal) else rch
        in node { val = val, left = updatedLeft, right = updatedRight }
  where
    defaultNode = Node { val = 0, left = Nothing, right = Nothing }


build:: Int -> Int -> Int -> Seq.Seq Int -> Node
build n l r arr 
    | l == r = Node {val = Seq.index arr (l - 1), left = Nothing, right = Nothing}
    | otherwise = 
        let m = (l + r) `div` 2
        in Node {val = -1, left = Just(build n l m arr), right = Just(build n (m + 1) r arr)}


query :: Node -> Int -> Int -> Int -> Int
query (Node val lch rch) l r p
    | l == r = val
    | otherwise =
        let m = (l + r) `div` 2
        in if p <= m 
           then maybe (-1) (\leftNode -> query leftNode l m p) lch
           else maybe (-1) (\rightNode -> query rightNode (m + 1) r p) rch


main :: IO ()
main = do
    startTime <- getCurrentTime
    firstLine <- getLine
    let [n, m] = map read (words firstLine) :: [Int]
    secondLine <- getLine
    let arr = map read (words secondLine) :: [Int]
    let array = Seq.fromList arr
    let root = build n 1 n array
    processOperations n m (Seq.fromList [root])
    endTime <- getCurrentTime
    let timeDiff = diffUTCTime endTime startTime
    hPutStrLn stderr $ "Elapsed time: " ++ show timeDiff

processOperations :: Int -> Int -> Nodes -> IO ()
processOperations _ 0 _ = return ()
processOperations n m roots = do
    line <- getLine
    let operation = map read (words line) :: [Int]
    root <- execute n operation roots
    processOperations n (m - 1) (roots Seq.|> root)